// SPDX-License-Identifier: GPL-2.0-or-later
// SPDX-FileCopyrightText: 2001-2004 Wolfgang Denk <wd@denx.de>, DENX Software Engineering

#include <common.h>
#include <command.h>
#include <complete.h>
#include <driver.h>
#include <unistd.h>
#include <init.h>
#include <dhcp.h>
#include <net.h>
#include <dma.h>
#include <of.h>
#include <of_net.h>
#include <linux/phy.h>
#include <errno.h>
#include <malloc.h>
#include <globalvar.h>
#include <environment.h>
#include <linux/ctype.h>
#include <linux/stat.h>

static uint64_t last_link_check;

LIST_HEAD(netdev_list);

struct eth_ethaddr {
	struct list_head list;
	u8 ethaddr[ETH_ALEN];
	int ethid;
	struct device_node *node;
};

static LIST_HEAD(ethaddr_list);

int eth_set_ethaddr(struct eth_device *edev, const char *ethaddr)
{
	int ret;

	ret = edev->set_ethaddr(edev, ethaddr);
	if (ret)
		return ret;

	memcpy(edev->ethaddr, ethaddr, ETH_ALEN);

	return 0;
}

static void register_preset_mac_address(struct eth_device *edev, const char *ethaddr)
{
	unsigned char ethaddr_str[sizeof("xx:xx:xx:xx:xx:xx")];

	if (is_valid_ether_addr(ethaddr)) {
		ethaddr_to_string(ethaddr, ethaddr_str);
		dev_info(&edev->dev, "got preset MAC address: %s\n", ethaddr_str);
		eth_set_ethaddr(edev, ethaddr);
	}
}

static int eth_get_registered_ethaddr(struct eth_device *edev, void *buf)
{
	struct eth_ethaddr *addr;
	struct device_node *node = NULL;

	if (edev->parent)
		node = edev->parent->device_node;

	list_for_each_entry(addr, &ethaddr_list, list) {
		if ((node && node == addr->node) ||
				addr->ethid == edev->dev.id) {
			memcpy(buf, addr->ethaddr, ETH_ALEN);
			return 0;
		}
	}
	return -EINVAL;
}

static void eth_drop_ethaddr(int ethid)
{
	struct eth_ethaddr *addr, *tmp;

	list_for_each_entry_safe(addr, tmp, &ethaddr_list, list) {
		if (addr->ethid == ethid) {
			list_del(&addr->list);
			free(addr);
			return;
		}
	}
}

void eth_register_ethaddr(int ethid, const char *ethaddr)
{
	struct eth_ethaddr *addr;
	struct eth_device *edev;

	eth_drop_ethaddr(ethid);

	for_each_netdev(edev) {
		if (edev->dev.id == ethid) {
			register_preset_mac_address(edev, ethaddr);
			return;
		}
	}

	addr = xzalloc(sizeof(*addr));
	addr->ethid = ethid;
	memcpy(addr->ethaddr, ethaddr, ETH_ALEN);
	list_add_tail(&addr->list, &ethaddr_list);
}

static struct eth_device *eth_get_by_node(struct device_node *node)
{
	struct eth_device *edev;

	for_each_netdev(edev) {
		if (!edev->parent)
			continue;
		if (!edev->parent->device_node)
			continue;
		if (edev->parent->device_node == node)
			return edev;
	}
	return NULL;
}

void of_eth_register_ethaddr(struct device_node *node, const char *ethaddr)
{
	struct eth_ethaddr *addr;
	struct eth_device *edev;

	edev = eth_get_by_node(node);
	if (edev) {
		register_preset_mac_address(edev, ethaddr);
		return;
	}

	addr = xzalloc(sizeof(*addr));
	addr->node = node;
	addr->ethid = -1;
	memcpy(addr->ethaddr, ethaddr, ETH_ALEN);
	list_add_tail(&addr->list, &ethaddr_list);
}

struct eth_device *eth_get_byname(const char *ethname)
{
	struct eth_device *edev;

	for_each_netdev(edev) {
		if (!strcmp(ethname, eth_name(edev)))
			return edev;
	}
	return NULL;
}

#ifdef CONFIG_AUTO_COMPLETE
int eth_complete(struct string_list *sl, char *instr)
{
	struct eth_device *edev;
	int len;

	len = strlen(instr);

	for_each_netdev(edev) {
		if (strncmp(instr, eth_name(edev), len))
			continue;

		string_list_add_asprintf(sl, "%s ", eth_name(edev));
	}
	return COMPLETE_CONTINUE;
}
#endif

/*
 * Check for link if we haven't done so for longer.
 */
static int eth_carrier_check(struct eth_device *edev, int force)
{
	int ret;

	if (!IS_ENABLED(CONFIG_PHYLIB))
		return 0;

	if (!edev->phydev)
		return 0;

	if (force)
		phy_wait_aneg_done(edev->phydev);

	if (force || is_timeout(last_link_check, 5 * SECOND) ||
			!edev->phydev->link) {
		ret = phy_update_status(edev->phydev);
		if (ret)
			return ret;
		last_link_check = get_time_ns();
	}

	return edev->phydev->link ? 0 : -ENETDOWN;
}

struct eth_q {
	struct eth_device *edev;
	int length;
	struct list_head list;
	void *data;
};

static int eth_queue(struct eth_device *edev, void *packet, int length)
{
	struct eth_q *q;

	q = xzalloc(sizeof(*q));
	if (!q)
		return -ENOMEM;

	q->data = dma_alloc(length);
	if (!q->data) {
		free(q);
		return -ENOMEM;
	}

	q->length = length;
	q->edev = edev;

	memcpy(q->data, packet, length);
	list_add_tail(&q->list, &edev->send_queue);

	return 0;
}

int eth_send(struct eth_device *edev, void *packet, int length)
{
	int ret;

	if (!edev->active)
		return -ENETDOWN;

	if (slice_acquired(eth_device_slice(edev)))
		return eth_queue(edev, packet, length);

	ret = eth_carrier_check(edev, 0);
	if (ret)
		return ret;

	slice_acquire(eth_device_slice(edev));

	led_trigger_network(LED_TRIGGER_NET_TX);

	ret = edev->send(edev, packet, length);

	slice_release(eth_device_slice(edev));

	return ret;
}

static void eth_do_work(struct eth_device *edev)
{
	struct eth_q *q, *tmp;
	int ret;

	if (!phy_acquired(edev->phydev)) {
		ret = eth_carrier_check(edev, 0);
		if (ret)
			return;
	}

	if (slice_acquired(eth_device_slice(edev)))
		return;

	slice_acquire(eth_device_slice(edev));

	edev->recv(edev);

	list_for_each_entry_safe(q, tmp, &edev->send_queue, list) {
		led_trigger_network(LED_TRIGGER_NET_TX);
		edev->send(edev, q->data, q->length);
		list_del(&q->list);
		free(q->data);
		free(q);
	}

	slice_release(eth_device_slice(edev));
}

int eth_rx(void)
{
	struct eth_device *edev;

	for_each_netdev(edev) {
		if (edev->active)
			eth_do_work(edev);
	}

	return 0;
}

static int eth_param_set_ethaddr(struct param_d *param, void *priv)
{
	struct eth_device *edev = priv;

	return eth_set_ethaddr(edev, edev->ethaddr);
}

#ifdef CONFIG_OFTREE
static void eth_of_fixup_node(struct device_node *root,
			      const char *node_path, int ethid,
			      const u8 ethaddr[ETH_ALEN])
{
	struct device_node *bb_node, *fixup_node;
	char *name;
	int ret;

	if (!is_valid_ether_addr(ethaddr)) {
		pr_debug("%s: no valid mac address, cannot fixup\n",
			 __func__);
		return;
	}

	if (node_path) {
		bb_node = of_find_node_by_path_from(0, node_path);
		name = of_get_reproducible_name(bb_node);
		fixup_node = of_find_node_by_reproducible_name(root, name);
		free(name);
	} else {
		char eth[12];
		sprintf(eth, "ethernet%d", ethid);
		fixup_node = of_find_node_by_alias(root, eth);
	}

	if (!fixup_node) {
		pr_debug("%s: no node to fixup\n", __func__);
		return;
	}

	ret = of_set_property(fixup_node, "mac-address", ethaddr, ETH_ALEN, 1);
	if (ret)
		pr_err("Setting mac-address property of %s failed with: %s\n",
		       fixup_node->full_name, strerror(-ret));
}

static int eth_of_fixup(struct device_node *root, void *unused)
{
	struct eth_ethaddr *addr;
	struct eth_device *edev;

	/*
	 * Add the mac-address property for each ethaddr and then each network
	 * device we find a node path for and which has a valid mac address.
	 * This will find both network devices barebox was told about as well as
	 * addresses registered by boards but for which no network device was
	 * ever loaded.
	 */
	list_for_each_entry(addr, &ethaddr_list, list)
		eth_of_fixup_node(root, addr->node ? addr->node->full_name : NULL,
				  addr->ethid, addr->ethaddr);

	for_each_netdev(edev)
		eth_of_fixup_node(root, edev->nodepath, edev->dev.id, edev->ethaddr);

	return 0;
}

static int eth_register_of_fixup(void)
{
	return of_register_fixup(eth_of_fixup, NULL);
}
late_initcall(eth_register_of_fixup);
#endif

extern char *net_server;
extern IPaddr_t net_gateway;

static const char * const eth_mode_names[] = {
	[ETH_MODE_DHCP] = "dhcp",
	[ETH_MODE_STATIC] = "static",
	[ETH_MODE_DISABLED] = "disabled",
};

int eth_register(struct eth_device *edev)
{
	struct device_d *dev = &edev->dev;
	unsigned char ethaddr[ETH_ALEN];
	int ret, found = 0;

	if (!edev->get_ethaddr) {
		dev_err(dev, "no get_mac_address found for current eth device\n");
		return -1;
	}

	dev_set_name(&edev->dev, "eth");

	if (edev->parent)
		edev->dev.parent = edev->parent;

	if (edev->dev.parent && edev->dev.parent->device_node) {
		edev->dev.id = of_alias_get_id(edev->dev.parent->device_node, "ethernet");
		if (edev->dev.id < 0)
			edev->dev.id = DEVICE_ID_DYNAMIC;
	} else {
		edev->dev.id = DEVICE_ID_DYNAMIC;
	}

	INIT_LIST_HEAD(&edev->send_queue);

	ret = register_device(&edev->dev);
	if (ret)
		return ret;

	slice_init(&edev->slice, dev_name(dev));

	edev->devname = xstrdup(dev_name(&edev->dev));

	dev_add_param_ip(dev, "ipaddr", NULL, NULL, &edev->ipaddr, edev);
	dev_add_param_string(dev, "serverip", NULL, NULL, &net_server, edev);
	dev_add_param_ip(dev, "gateway", NULL, NULL, &net_gateway, edev);
	dev_add_param_ip(dev, "netmask", NULL, NULL, &edev->netmask, edev);
	dev_add_param_mac(dev, "ethaddr", eth_param_set_ethaddr, NULL,
			edev->ethaddr, edev);
	edev->bootarg = xstrdup("");
	dev_add_param_string(dev, "linux.bootargs", NULL, NULL, &edev->bootarg, NULL);
	edev->linuxdevname = xstrdup("");
	dev_add_param_string(dev, "linux.devname", NULL, NULL, &edev->linuxdevname, NULL);
	dev_add_param_enum(dev, "mode", NULL, NULL, &edev->global_mode,
				  eth_mode_names, ARRAY_SIZE(eth_mode_names),
				  NULL);

	if (edev->init)
		edev->init(edev);

	list_add_tail(&edev->list, &netdev_list);

	ret = eth_get_registered_ethaddr(edev, ethaddr);
	if (!ret)
		found = 1;

	if (!found) {
		ret = edev->get_ethaddr(edev, ethaddr);
		if (!ret)
			found = 1;
	}

	if (found)
		register_preset_mac_address(edev, ethaddr);

	if (IS_ENABLED(CONFIG_OFDEVICE) && edev->parent &&
			edev->parent->device_node)
		edev->nodepath = xstrdup(edev->parent->device_node->full_name);

	return 0;
}

int eth_open(struct eth_device *edev)
{
	int ret;

	if (edev->active)
		return 0;

	ret = edev->open(edev);
	if (!ret)
		edev->active = 1;

	eth_carrier_check(edev, 1);

	return ret;
}

void eth_close(struct eth_device *edev)
{
	if (!edev->active)
		return;

	edev->halt(edev);

	edev->active = 0;
}

void eth_unregister(struct eth_device *edev)
{
	struct eth_q *q, *tmp;

	if (edev->active)
		edev->halt(edev);

	list_for_each_entry_safe(q, tmp, &edev->send_queue, list) {
		if (q->edev != edev)
			continue;

		list_del(&q->list);
		free(q->data);
		free(q);
	}

	if (IS_ENABLED(CONFIG_OFDEVICE))
		free(edev->nodepath);

	free(edev->devname);

	unregister_device(&edev->dev);
	slice_exit(&edev->slice);
	list_del(&edev->list);
}

void led_trigger_network(enum led_trigger trigger)
{
	led_trigger(trigger, TRIGGER_FLASH);
	led_trigger(LED_TRIGGER_NET_TXRX, TRIGGER_FLASH);
}

static int of_populate_ethaddr(void)
{
	char str[sizeof("xx:xx:xx:xx:xx:xx")];
	struct eth_device *edev;
	int ret;

	list_for_each_entry(edev, &netdev_list, list) {
		if (!edev->parent || is_valid_ether_addr(edev->ethaddr))
			continue;

		ret = of_get_mac_addr_nvmem(edev->parent->device_node, edev->ethaddr);
		if (ret)
			continue;

		ethaddr_to_string(edev->ethaddr, str);
		dev_info(&edev->dev, "Got preset MAC address from device tree: %s\n", str);
		eth_set_ethaddr(edev, edev->ethaddr);
	}

	return 0;
}
postenvironment_initcall(of_populate_ethaddr);
