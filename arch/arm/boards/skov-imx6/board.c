// SPDX-License-Identifier: GPL-2.0-only

#define pr_fmt(fmt) "skov-imx6: " fmt

#include <common.h>
#include <init.h>
#include <mach/bbu.h>
#include <environment.h>
#include <bootsource.h>
#include <globalvar.h>
#include <net.h>
#include <of_gpio.h>
#include <gpio.h>

#include "version.h"

static int eth_of_fixup_node(struct device_node *root, const char *node_path,
			     const u8 *ethaddr)
{
	struct device_node *node;
	int ret;

	if (!is_valid_ether_addr(ethaddr)) {
		unsigned char ethaddr_str[sizeof("xx:xx:xx:xx:xx:xx")];

		ethaddr_to_string(ethaddr, ethaddr_str);
		pr_err("The mac-address %s is invalid.\n", ethaddr_str);
		return -EINVAL;
	}

	node = of_find_node_by_path_from(root, node_path);
	if (!node) {
		pr_err("Did not find node %s to fix up with stored mac-address.\n",
		       node_path);
		return -ENOENT;
	}

	ret = of_set_property(node, "mac-address", ethaddr, ETH_ALEN, 1);
	if (ret)
		pr_err("Setting mac-address property of %s failed with: %s.\n",
		       node->full_name, strerror(-ret));

	return ret;
}

static int eth_of_fixup_node_from_eth_device(struct device_node *root,
					     const char *node_path,
					     const char *ethname)
{
	struct eth_device *edev;

	edev = eth_get_byname(ethname);
	if (!edev) {
		pr_err("Did not find eth device \"%s\" to copy mac-address from.\n", ethname);
		return -ENOENT;
	}

	return eth_of_fixup_node(root, node_path, edev->ethaddr);
}

static int get_mac_address_from_env_variable(const char *env, u8 ethaddr[ETH_ALEN])
{
	const char *ethaddr_str;
	int ret;

	ethaddr_str = getenv(env);
	if (!ethaddr_str) {
		pr_err("State variable %s storing the mac-address not found.\n", env);
		return -ENOENT;
	}

	ret = string_to_ethaddr(ethaddr_str, ethaddr);
	if (ret < 0) {
		pr_err("Could not convert \"%s\" in state variable %s into mac-address.\n",
		       ethaddr_str, env);
		return -EINVAL;
	}

	return 0;
}

static int get_default_mac_address_from_state_node(const char *state_node_path,
						   u8 ethaddr[ETH_ALEN])
{
	struct device_node *node;
	int ret;

	node = of_find_node_by_path(state_node_path);
	if (!node) {
		pr_err("Node %s defining the state variable not found.\n", state_node_path);
		return -ENOENT;
	}

	ret = of_property_read_u8_array(node, "default", ethaddr, ETH_ALEN);
	if (ret) {
		pr_err("Node %s has no property \"default\" of proper type.\n", state_node_path);
		return -ENOENT;
	}

	return 0;
}

static int eth2_of_fixup_node_individually(struct device_node *root,
					   const char *node_path,
					   const char *ethname,
					   const char *env,
					   const char *state_node_path)
{
	u8 env_ethaddr[ETH_ALEN], default_ethaddr[ETH_ALEN];
	int ret;

	ret = get_mac_address_from_env_variable(env, env_ethaddr);
	if (ret)
		goto copy_mac_from_eth0;

	ret = get_default_mac_address_from_state_node(state_node_path, default_ethaddr);
	if (ret)
		goto copy_mac_from_eth0;

	/*
	 * As the default is bogus copy the MAC address from eth0 if
	 * the state variable has not been set to a different variant
	 */
	if (memcmp(env_ethaddr, default_ethaddr, ETH_ALEN) == 0)
		goto copy_mac_from_eth0;

	return eth_of_fixup_node(root, node_path, env_ethaddr);

copy_mac_from_eth0:
	return eth_of_fixup_node_from_eth_device(root, node_path, ethname);
}

#define MAX_V_GPIO 8

struct board_description {
	const char *variant;
	const char *revision;
	const char *soc;
	const char *dts_compatible;
	const char *display;
	unsigned flags;
};

#define SKOV_NEED_ENABLE_RMII	BIT(0)
#define SKOV_DISPLAY_PARALLEL	BIT(1)
#define SKOV_ENABLE_MMC_POWER	BIT(2)
#define SKOV_DISPLAY_LVDS	BIT(3)

static const struct board_description imx6_variants[] = {
	[0] = {
		.variant = "high performance",
		.revision = "A",
		.soc = "i.MX6Q",
		.dts_compatible = "skov,imx6-imxq-revA",
		.flags = SKOV_NEED_ENABLE_RMII | SKOV_DISPLAY_PARALLEL,
	},
	[1] = {
		.variant = "low cost",
		.revision = "A",
		.soc = "i.MX6S",
		.dts_compatible = "skov,imx6-imxdl-revA",
		.flags = SKOV_NEED_ENABLE_RMII | SKOV_DISPLAY_PARALLEL,
	},
	[2] = {
		.variant = "high performance",
		.revision = "A",
		.soc = "i.MX6Q",
		.dts_compatible = "skov,imx6-imxq-revA",
		.flags = SKOV_NEED_ENABLE_RMII | SKOV_DISPLAY_PARALLEL,
	},
	[4] = {
		.variant = "low cost",
		.revision = "A",
		.soc = "i.MX6S",
		.dts_compatible = "skov,imx6-imxdl-revA",
		.flags = SKOV_NEED_ENABLE_RMII | SKOV_DISPLAY_PARALLEL,
	},
	[8] = {
		.variant = "high performance",
		.revision = "A",
		.soc = "i.MX6Q",
		.dts_compatible = "skov,imx6-imxq-revA",
		.flags = SKOV_NEED_ENABLE_RMII | SKOV_DISPLAY_PARALLEL,
	},
	[9] = {
		.variant = "minimum cost",
		.revision = "B",
		.soc = "i.MX6S",
		.dts_compatible = "skov,imx6-imxdl-revB",
		.flags = SKOV_DISPLAY_PARALLEL,
	},
	[10] = {
		.variant = "low cost",
		.revision = "B",
		.soc = "i.MX6S",
		.dts_compatible = "skov,imx6-imxdl-revB",
		.flags = SKOV_DISPLAY_PARALLEL,
	},
	[11] = {
		.variant = "high performance",
		.revision = "B",
		.soc = "i.MX6Q",
		.dts_compatible = "skov,imx6-imxq-revB",
		.flags = SKOV_DISPLAY_PARALLEL,
	},
	[12] = {
		/* FIXME this one is a revision 'C' according to the schematics */
		.variant = "max performance",
		.revision = "B",
		.soc = "i.MX6Q",
		.dts_compatible = "skov,imx6q-skov-revc-lt2",
		.display = "l2rt",
		.flags = SKOV_DISPLAY_PARALLEL,
	},
	[13] = {
		.variant = "low cost",
		.revision = "C",
		.soc = "i.MX6S",
		.dts_compatible = "skov,imx6dl-skov-revc-lt2",
		.display = "l2rt",
		.flags = SKOV_ENABLE_MMC_POWER | SKOV_DISPLAY_PARALLEL,
	},
	[14] = {
		.variant = "high performance",
		.revision = "C",
		.soc = "i.MX6Q",
		.dts_compatible = "skov,imx6q-skov-revc-lt2",
		.display = "l2rt",
		.flags = SKOV_ENABLE_MMC_POWER | SKOV_DISPLAY_PARALLEL,
	},
	[15] = {
		.variant = "middle performance",
		.revision = "C",
		.soc = "i.MX6S",
		.dts_compatible = "skov,imx6dl-skov-revc-lt2",
		.display = "l2rt",
		.flags = SKOV_ENABLE_MMC_POWER | SKOV_DISPLAY_PARALLEL,
	},
	[16] = {
		.variant = "Solo_R512M_F4G",
		.revision = "C",
		.soc = "i.MX6S",
		.dts_compatible = "skov,imx6dl-skov-revc-lt2",
		.display = "l2rt",
		.flags = SKOV_ENABLE_MMC_POWER | SKOV_DISPLAY_PARALLEL,
	},
	[17] = {
		.variant = "Quad_R2G_F8G",
		.revision = "C",
		.soc = "i.MX6Q",
		.dts_compatible = "skov,imx6q-skov-revc-lt2",
		.display = "l2rt",
		.flags = SKOV_ENABLE_MMC_POWER | SKOV_DISPLAY_PARALLEL,
	},
	[18] = {
		.variant = "QuadPlus_R4G_F16G",
		.revision = "C",
		.soc = "i.MX6Q+",
		.dts_compatible = "skov,imx6q-skov-revc-lt2",
		.display = "l2rt",
		.flags = SKOV_ENABLE_MMC_POWER | SKOV_DISPLAY_PARALLEL,
	},
	[19] = {
		.variant = "Solo_R512M_F2G",
		.revision = "C",
		.soc = "i.MX6S",
		.dts_compatible = "skov,imx6dl-skov-revc-lt2",
		.display = "l2rt",
		.flags = SKOV_ENABLE_MMC_POWER | SKOV_DISPLAY_PARALLEL,
	},
	[20] = {
		.variant = "Quad_R1G_F4G",
		.revision = "C",
		.soc = "i.MX6Q",
		.dts_compatible = "skov,imx6q-skov-revc-lt2",
		.display = "l2rt",
		.flags = SKOV_ENABLE_MMC_POWER | SKOV_DISPLAY_PARALLEL,
	},
	[21] = {
		.variant = "Solo_R512M_F2G",
		.revision = "C",
		.soc = "i.MX6S",
		.dts_compatible = "skov,imx6dl-skov-revc-lt6",
		.display = "l6whrt",
		.flags = SKOV_ENABLE_MMC_POWER | SKOV_DISPLAY_PARALLEL,
	},
	[22] = {
		.variant = "Quad_R1G_F4G",
		.revision = "C",
		.soc = "i.MX6Q",
		.dts_compatible = "skov,imx6q-skov-revc-lt6",
		.display = "l6whrt",
		.flags = SKOV_ENABLE_MMC_POWER | SKOV_DISPLAY_PARALLEL,
	},
	[24] = {
		.variant = "Quad_R1G_F4G",
		.revision = "E",
		.soc = "i.MX6Q",
		.dts_compatible = "skov,imx6q-skov-reve-mi1010ait-1cp1",
		.display = "mi1010ait-1cp1",
		.flags = SKOV_ENABLE_MMC_POWER | SKOV_DISPLAY_LVDS,
	},
};

static int skov_board_no = -1;

static int skov_imx6_fixup(struct device_node *root, void *unused)
{
	int ret;
	const char *val;
	uint32_t brightness;
	struct device_node *node;
	struct device_node *chosen = of_create_node(root, "/chosen");

	eth_of_fixup_node_from_eth_device(root,
			"/mdio-gpio/ksz8873@3/ports/ports@0", "eth0");
	eth2_of_fixup_node_individually(root,
		"/mdio-gpio/ksz8873@3/ports/ports@1", "eth0",
		"state.ethaddr.eth2", "/state/ethaddr/eth2");

	switch (bootsource_get()) {
	case BOOTSOURCE_MMC:
		/* use default variant of state variable defined in devicetree */
		brightness = 8;
		break;
	default:
		val = getenv("state.display.brightness");
		if (!val) {
			pr_err("could not get default display brightness\n");
			return 0;
		}

		brightness = simple_strtoul(val, NULL, 0);
		break;
	}

	for_each_compatible_node_from(node, root, NULL, "pwm-backlight") {
		ret = of_property_write_u32(node, "default-brightness-level", brightness);
		if (ret)
			pr_err("error %d while setting default-brightness-level property on node %s to %d\n",
				ret, node->name, brightness);
	}

	of_property_write_u32(chosen, "skov,imx6-board-version", skov_board_no);
	of_property_write_string(chosen, "skov,imx6-board-variant",
				 imx6_variants[skov_board_no].variant);

	return 0;
}

/*
 * Some variants need tweaks to make them work
 *
 * Revision A has no backlight control, since revision B it is present (GPIO6/23)
 * Revision A needs GPIO1/24 to be low to make network working
 * Revision C can control the SD main power supply
 */
static void skov_init_board(const struct board_description *variant)
{
	struct device_node *np;
	char *environment_path, *envdev;
	int ret;

	imx6_bbu_internal_spi_i2c_register_handler("spiflash", "/dev/m25p0.barebox",
		BBU_HANDLER_FLAG_DEFAULT);

	of_register_fixup(skov_imx6_fixup, NULL);

	switch (bootsource_get()) {
	case BOOTSOURCE_MMC:
		environment_path = "/chosen/environment-sd";
		envdev = "MMC";
		break;
	default:
		environment_path = "/chosen/environment-spinor";
		envdev = "SPI NOR flash";
		break;
	}

	pr_notice("Using environment in %s\n", envdev);

	ret = of_device_enable_path(environment_path);
	if (ret < 0)
		pr_warn("Failed to enable environment partition '%s' (%d)\n",
			environment_path, ret);

	if (variant->flags & SKOV_NEED_ENABLE_RMII) {
		/*
		 * MX6QDL_PAD_ENET_RX_ER__GPIO1_IO24 is a gpio which must be
		 * low to enable the RMII from the switch point of view
		 */
		gpio_request(24, "must_be_low");
		gpio_direction_output(24, 0);
	}

	/* SD card handling */
	gpio_request(205, "mmc io supply");
	gpio_direction_output(205, 0); /* select 3.3 V IO voltage */

	if (variant->flags & SKOV_ENABLE_MMC_POWER) {
		/*
		 * keep in sync with devicetree's 'regulator-boot-on' setting for
		 * this regulator
		 */
		gpio_request(200, "mmc power supply");
		gpio_direction_output(200, 0); /* switch on */
		mdelay(1);
		gpio_direction_output(200, 1); /* switch on */
	}

	if (variant->flags & SKOV_DISPLAY_PARALLEL) {
		np = of_find_compatible_node(NULL, NULL, "fsl,imx-parallel-display");
		if (np)
			of_device_enable_and_register(np);
		else
			pr_err("Cannot find \"fsl,imx-parallel-display\" node\n");
	}

	if (variant->flags & SKOV_DISPLAY_LVDS) {
		np = of_find_compatible_node(NULL, NULL, "fsl,imx6q-ldb");
		if (np)
			of_device_enable_and_register(np);
		else
			pr_err("Cannot find \"fsl,imx6q-ldb\" node\n");

		/* ... as well as its channel 0 */
		np = of_find_node_by_name(np, "lvds-channel@0");
		if (np)
			of_device_enable(np);
		else
			pr_err("Cannot find \"lvds-channel@0\" node\n");
	}
}

static void fixup_machine_compatible(const char *compat)
{
	const char *curcompat;
	struct device_node *root;
	int cclen = 0, clen = strlen(compat) + 1;
	void *buf;

	root = of_get_root_node();
	if (!root)
		return;

	curcompat = of_get_property(root, "compatible", &cclen);

	buf = xzalloc(cclen + clen);

	memcpy(buf, compat, clen);
	memcpy(buf + clen, curcompat, cclen);

	/*
	 * Prepend the compatible from board entry to the machine compatible.
	 * Used to match bootspec entries against it.
	 */
	of_set_property(root, "compatible", buf, cclen + clen, true);

	free(buf);
}

static int skov_imx6_probe(struct device_d *dev)
{
	unsigned v = 0;
	const struct board_description *variant;

	v = skov_imx6_get_version();

	if (v >= ARRAY_SIZE(imx6_variants)) {
		dev_err(dev, "Invalid variant %u\n", v);
		return -EINVAL;
	}

	variant = &imx6_variants[v];

	if (!variant->variant) {
		dev_err(dev, "Invalid variant %u\n", v);
		return -EINVAL;
	}

	skov_board_no = v;

	globalvar_add_simple_int("board.no", &skov_board_no, "%u");
	globalvar_add_simple("board.variant", variant->variant);
	globalvar_add_simple("board.revision",variant->revision);
	globalvar_add_simple("board.soc", variant->soc);
	globalvar_add_simple("board.dts", variant->dts_compatible);
	globalvar_add_simple("board.display", variant->display ?: NULL);

	fixup_machine_compatible(variant->dts_compatible);

	skov_init_board(variant);

	return 0;
}

static __maybe_unused struct of_device_id skov_version_ids[] = {
	{
		.compatible = "skov,imx6",
	}, {
		/* sentinel */
	}
};

static struct driver_d skov_version_driver = {
	.name = "skov-imx6",
	.probe = skov_imx6_probe,
	.of_compatible = DRV_OF_COMPAT(skov_version_ids),
};
coredevice_platform_driver(skov_version_driver);

static void skov_imx6_devices_shutdown(void)
{
	const char *external;

	if (skov_board_no < 0)
		return;

	external = getenv("state.display.external");
	if (!external) {
		pr_err("could not get state variable display.external\n");
		return;
	}

	if (!strcmp(external, "0"))
		setenv("backlight0.brightness", "0");
}
predevshutdown_exitcall(skov_imx6_devices_shutdown);
