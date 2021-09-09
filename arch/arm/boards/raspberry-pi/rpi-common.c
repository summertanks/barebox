// SPDX-License-Identifier: GPL-2.0-or-later
// SPDX-FileCopyrightText: 2009 Carlo Caione <carlo@carlocaione.org>

#include <common.h>
#include <init.h>
#include <fs.h>
#include <of.h>
#include <linux/stat.h>
#include <linux/clk.h>
#include <linux/clkdev.h>
#include <envfs.h>
#include <regulator.h>
#include <malloc.h>
#include <libfile.h>
#include <gpio.h>
#include <net.h>
#include <led.h>
#include <asm/armlinux.h>
#include <asm/barebox-arm.h>
#include <generated/mach-types.h>
#include <linux/sizes.h>
#include <globalvar.h>
#include <asm/system_info.h>

#include <mach/core.h>
#include <mach/mbox.h>
#include <mach/platform.h>

#include "lowlevel.h"

struct rpi_model {
	const char *name;
	void (*init)(void);
};

#define RPI_MODEL(_id, _name, _init)	\
	[_id] = {				\
		.name			= _name,\
		.init			= _init,\
	}

struct msg_get_arm_mem {
	struct bcm2835_mbox_hdr hdr;
	struct bcm2835_mbox_tag_get_arm_mem get_arm_mem;
	u32 end_tag;
};

struct msg_get_clock_rate {
	struct bcm2835_mbox_hdr hdr;
	struct bcm2835_mbox_tag_get_clock_rate get_clock_rate;
	u32 end_tag;
};

struct msg_get_board_rev {
	struct bcm2835_mbox_hdr hdr;
	struct bcm2835_mbox_tag_get_board_rev get_board_rev;
	u32 end_tag;
};

struct msg_get_mac_address {
	struct bcm2835_mbox_hdr hdr;
	struct bcm2835_mbox_tag_get_mac_address get_mac_address;
	u32 end_tag;
};

static int rpi_get_arm_mem(u32 *size)
{
	BCM2835_MBOX_STACK_ALIGN(struct msg_get_arm_mem, msg);
	int ret;

	BCM2835_MBOX_INIT_HDR(msg);
	BCM2835_MBOX_INIT_TAG(&msg->get_arm_mem, GET_ARM_MEMORY);

	ret = bcm2835_mbox_call_prop(BCM2835_MBOX_PROP_CHAN, &msg->hdr);
	if (ret)
		return ret;

	*size = msg->get_arm_mem.body.resp.mem_size;

	return 0;
}

static struct clk *rpi_register_firmware_clock(u32 clock_id, const char *name)
{
	BCM2835_MBOX_STACK_ALIGN(struct msg_get_clock_rate, msg);
	int ret;

	BCM2835_MBOX_INIT_HDR(msg);
	BCM2835_MBOX_INIT_TAG(&msg->get_clock_rate, GET_CLOCK_RATE);
	msg->get_clock_rate.body.req.clock_id = clock_id;

	ret = bcm2835_mbox_call_prop(BCM2835_MBOX_PROP_CHAN, &msg->hdr);
	if (ret)
		return ERR_PTR(ret);

	return clk_fixed(name, msg->get_clock_rate.body.resp.rate_hz);
}

static void rpi_set_usbethaddr(void)
{
	BCM2835_MBOX_STACK_ALIGN(struct msg_get_mac_address, msg);
	int ret;

	BCM2835_MBOX_INIT_HDR(msg);
	BCM2835_MBOX_INIT_TAG(&msg->get_mac_address, GET_MAC_ADDRESS);

	ret = bcm2835_mbox_call_prop(BCM2835_MBOX_PROP_CHAN, &msg->hdr);
	if (ret) {
		printf("bcm2835: Could not query MAC address\n");
		/* Ignore error; not critical */
		return;
	}

	eth_register_ethaddr(0, msg->get_mac_address.body.resp.mac);
}

static void rpi_set_usbotg(const char *alias)
{
	struct device_node *usb;

	usb = of_find_node_by_alias(NULL, alias);
	if (usb)
		of_property_write_string(usb, "dr_mode", "otg");
}

static struct gpio_led rpi_leds[] = {
	{
		.gpio	= -EINVAL,
		.led	= {
			.name = "ACT",
		},
	}, {
		.gpio	= -EINVAL,
		.led	= {
			.name = "PWR",
		},
	},
};

static void rpi_add_led(void)
{
	int i;
	struct gpio_led *l;

	for (i = 0; i < ARRAY_SIZE(rpi_leds); i++) {
		l = &rpi_leds[i];

		if (gpio_is_valid(l->gpio))
			led_gpio_register(l);
	}

	l = &rpi_leds[0];
	if (gpio_is_valid(l->gpio))
		led_set_trigger(LED_TRIGGER_HEARTBEAT, &l->led);
}

static void rpi_b_init(void)
{
	rpi_leds[0].gpio = 16;
	rpi_leds[0].active_low = 1;
	rpi_set_usbethaddr();
}

static void rpi_b_plus_init(void)
{
	rpi_leds[0].gpio = 47;
	rpi_leds[1].gpio = 35;
	rpi_set_usbethaddr();
}

static void rpi_0_init(void)
{
	rpi_leds[0].gpio = 47;
	rpi_set_usbotg("usb0");
}

static void rpi_0_w_init(void)
{
	struct device_node *np;
	int ret;

	rpi_0_init();

	np = of_find_node_by_path("/chosen");
	if (!np)
		return;

	if (!of_device_enable_and_register_by_alias("serial1"))
		return;

	ret = of_property_write_string(np, "stdout-path", "serial1:115200n8");
	if (ret)
		return;

	of_device_disable_by_alias("serial0");
}

/* See comments in mbox.h for data source */
static const struct rpi_model rpi_models_old_scheme[] = {
	RPI_MODEL(0, "Unknown model", NULL),
	RPI_MODEL(BCM2835_BOARD_REV_B_I2C0_2, "Model B (no P5)", rpi_b_init),
	RPI_MODEL(BCM2835_BOARD_REV_B_I2C0_3, "Model B (no P5)", rpi_b_init),
	RPI_MODEL(BCM2835_BOARD_REV_B_I2C1_4, "Model B", rpi_b_init),
	RPI_MODEL(BCM2835_BOARD_REV_B_I2C1_5, "Model B", rpi_b_init),
	RPI_MODEL(BCM2835_BOARD_REV_B_I2C1_6, "Model B", rpi_b_init),
	RPI_MODEL(BCM2835_BOARD_REV_A_7, "Model A", NULL),
	RPI_MODEL(BCM2835_BOARD_REV_A_8, "Model A", NULL),
	RPI_MODEL(BCM2835_BOARD_REV_A_9, "Model A", NULL),
	RPI_MODEL(BCM2835_BOARD_REV_B_REV2_d, "Model B rev2", rpi_b_init),
	RPI_MODEL(BCM2835_BOARD_REV_B_REV2_e, "Model B rev2", rpi_b_init),
	RPI_MODEL(BCM2835_BOARD_REV_B_REV2_f, "Model B rev2", rpi_b_init),
	RPI_MODEL(BCM2835_BOARD_REV_B_PLUS_10, "Model B+", rpi_b_plus_init),
	RPI_MODEL(BCM2835_BOARD_REV_CM_11, "Compute Module", NULL),
	RPI_MODEL(BCM2835_BOARD_REV_A_PLUS_12, "Model A+", NULL),
	RPI_MODEL(BCM2835_BOARD_REV_B_PLUS_13, "Model B+", rpi_b_plus_init),
	RPI_MODEL(BCM2835_BOARD_REV_CM_14, "Compute Module", NULL),
	RPI_MODEL(BCM2835_BOARD_REV_A_PLUS_15, "Model A+", NULL),
};

static const struct rpi_model rpi_models_new_scheme[] = {
	RPI_MODEL(BCM2835_BOARD_REV_A, 		"Model A",	NULL ),
	RPI_MODEL(BCM2835_BOARD_REV_B, 		"Model B", 	rpi_b_init ),
	RPI_MODEL(BCM2835_BOARD_REV_A_PLUS, 	"Model A+", 	NULL ),
	RPI_MODEL(BCM2835_BOARD_REV_B_PLUS, 	"Model B+", 	rpi_b_plus_init ),
	RPI_MODEL(BCM2836_BOARD_REV_2_B, 	"Model 2B", 	rpi_b_plus_init),
	RPI_MODEL(BCM283x_BOARD_REV_Alpha, 	"Alpha", 	NULL),
	RPI_MODEL(BCM2835_BOARD_REV_CM1, 	"Compute Module", NULL ),
	RPI_MODEL(0x7, "Unknown model", NULL),
	RPI_MODEL(BCM2837_BOARD_REV_3_B, 	"Model 3B", 	rpi_b_init ),
	RPI_MODEL(BCM2835_BOARD_REV_ZERO, 	"Zero", 	rpi_0_init),
	RPI_MODEL(BCM2837_BOARD_REV_CM3, 	"Compute Module 3", NULL ),
	RPI_MODEL(0xb, "Unknown model", NULL),
	RPI_MODEL(BCM2835_BOARD_REV_ZERO_W, 	"Zero W", 	rpi_0_w_init),
	RPI_MODEL(BCM2837B0_BOARD_REV_3B_PLUS, 	"Model 3B+", 	rpi_b_plus_init ),
	RPI_MODEL(BCM2837B0_BOARD_REV_3A_PLUS, 	"Model 3A+", 	rpi_b_plus_init),
	RPI_MODEL(0xf, "Unknown model", NULL),
	RPI_MODEL(BCM2837B0_BOARD_REV_CM3_PLUS, "Compute Module 3+", NULL),
};

static int rpi_board_rev = 0;
static const struct rpi_model *model = NULL;

static void rpi_get_board_rev(void)
{
	int ret;
	char *name;
	const struct rpi_model *rpi_models;
	size_t rpi_models_size;

	BCM2835_MBOX_STACK_ALIGN(struct msg_get_board_rev, msg);
	BCM2835_MBOX_INIT_HDR(msg);
	BCM2835_MBOX_INIT_TAG(&msg->get_board_rev, GET_BOARD_REV);

	ret = bcm2835_mbox_call_prop(BCM2835_MBOX_PROP_CHAN, &msg->hdr);
	if (ret) {
		printf("bcm2835: Could not query board revision\n");
		/* Ignore error; not critical */
		return;
	}

	/* Comments from u-boot:
	 * For details of old-vs-new scheme, see:
	 * https://github.com/pimoroni/RPi.version/blob/master/RPi/version.py
	 * http://www.raspberrypi.org/forums/viewtopic.php?f=63&t=99293&p=690282
	 * (a few posts down)
	 *
	 * For the RPi 1, bit 24 is the "warranty bit", so we mask off just the
	 * lower byte to use as the board rev:
	 * http://www.raspberrypi.org/forums/viewtopic.php?f=63&t=98367&start=250
	 * http://www.raspberrypi.org/forums/viewtopic.php?f=31&t=20594
	 */
	rpi_board_rev = msg->get_board_rev.body.resp.rev;
	if (rpi_board_rev & 0x800000) {
		rpi_board_rev = (rpi_board_rev >> 4) & 0xff;
		rpi_models = rpi_models_new_scheme;
		rpi_models_size = ARRAY_SIZE(rpi_models_new_scheme);

	} else {
		rpi_board_rev &= 0xff;
		rpi_models = rpi_models_old_scheme;
		rpi_models_size = ARRAY_SIZE(rpi_models_old_scheme);
	}

	if (rpi_board_rev >= rpi_models_size) {
		printf("RPI: Board rev %u outside known range\n",
		       rpi_board_rev);
		goto unknown_rev;
	}

	if (!rpi_models[rpi_board_rev].name) {
		printf("RPI: Board rev %u unknown\n", rpi_board_rev);
		goto unknown_rev;
	}

	if (!rpi_board_rev)
		goto unknown_rev;

	model = &rpi_models[rpi_board_rev];
	name = basprintf("RaspberryPi %s", model->name);
	barebox_set_model(name);
	free(name);

	return;

unknown_rev:
	rpi_board_rev = 0;
	barebox_set_model("RaspberryPi (unknown rev)");
}

static void rpi_model_init(void)
{
	if (!model)
		return;

	if (!model->init)
		return;

	model->init();
}

static int rpi_mem_init(void)
{
	u32 size = 0;
	int ret;

	ret = rpi_get_arm_mem(&size);
	if (ret)
		printf("could not query ARM memory size\n");

	bcm2835_add_device_sdram(size);

	return ret;
}
mem_initcall(rpi_mem_init);

static int rpi_postcore_init(void)
{
	rpi_get_board_rev();
	barebox_set_hostname("rpi");
	rpi_model_init();

	return 0;
}
postcore_initcall(rpi_postcore_init);

static int rpi_clock_init(void)
{
	struct clk *clk;

	clk = rpi_register_firmware_clock(BCM2835_MBOX_CLOCK_ID_EMMC,
					 "bcm2835_mci0");
	if (IS_ERR(clk))
		return PTR_ERR(clk);

	clkdev_add_physbase(clk, 0x20300000, NULL);
	clkdev_add_physbase(clk, 0x3f300000, NULL);

	clk = rpi_register_firmware_clock(BCM2835_MBOX_CLOCK_ID_CORE,
					  "bcm2835_sdhost");
	if (IS_ERR(clk))
		return PTR_ERR(clk);

	clkdev_add_physbase(clk, 0x20202000, NULL);
	clkdev_add_physbase(clk, 0x3f202000, NULL);

	return 0;
}
postconsole_initcall(rpi_clock_init);

static int rpi_console_clock_init(void)
{
	struct clk *clk;

	clk = clk_fixed("apb_pclk", 0);
	clk_register_clkdev(clk, "apb_pclk", NULL);

	clk = clk_fixed("uart0-pl0110", 3 * 1000 * 1000);
	clk_register_clkdev(clk, NULL, "uart0-pl0110");
	clkdev_add_physbase(clk, BCM2835_PL011_BASE, NULL);
	clkdev_add_physbase(clk, BCM2836_PL011_BASE, NULL);

	clk = rpi_register_firmware_clock(BCM2835_MBOX_CLOCK_ID_CORE,
					  "uart1-8250");
	if (IS_ERR(clk))
		return PTR_ERR(clk);

	clkdev_add_physbase(clk, BCM2835_MINIUART_BASE, NULL);
	clkdev_add_physbase(clk, BCM2836_MINIUART_BASE, NULL);

	clk = clk_fixed("bcm2835-cs", 1 * 1000 * 1000);
	clk_register_clkdev(clk, NULL, "bcm2835-cs");

	return 0;
}
postcore_initcall(rpi_console_clock_init);

static int rpi_env_init(void)
{
	struct stat s;
	const char *diskdev = "/dev/disk0.0";
	int ret;

	device_detect_by_name("mci0");

	ret = stat(diskdev, &s);
	if (ret) {
		printf("no %s. using default env\n", diskdev);
		return 0;
	}

	mkdir("/boot", 0666);
	ret = mount(diskdev, "fat", "/boot", NULL);
	if (ret) {
		printf("failed to mount %s\n", diskdev);
		return 0;
	}

	defaultenv_append_directory(defaultenv_rpi);

	default_environment_path_set("/boot/barebox.env");

	return 0;
}

/* Extract /chosen/bootargs from the VideoCore FDT into vc.bootargs
 * global variable. */
static int rpi_vc_fdt_bootargs(void *fdt)
{
	int ret = 0;
	struct device_node *root = NULL, *node;
	const char *cmdline;

	root = of_unflatten_dtb(fdt, INT_MAX);
	if (IS_ERR(root)) {
		ret = PTR_ERR(root);
		root = NULL;
		goto out;
	}

	node = of_find_node_by_path_from(root, "/chosen");
	if (!node) {
		pr_err("no /chosen node\n");
		ret = -ENOENT;
		goto out;
	}

	cmdline = of_get_property(node, "bootargs", NULL);
	if (!cmdline) {
		pr_err("no bootargs property in the /chosen node\n");
		ret = -ENOENT;
		goto out;
	}

	globalvar_add_simple("vc.bootargs", cmdline);

	switch(cpu_architecture()) {
	case CPU_ARCH_ARMv6:
		globalvar_add_simple("vc.kernel", "kernel.img");
		break;
	case CPU_ARCH_ARMv7:
		globalvar_add_simple("vc.kernel", "kernel7.img");
		break;
	case CPU_ARCH_ARMv8:
		globalvar_add_simple("vc.kernel", "kernel7l.img");
		break;
	}

out:
	if (root)
		of_delete_node(root);

	return ret;
}

static void rpi_vc_fdt(void)
{
	void *saved_vc_fdt;
	struct fdt_header *oftree;
	unsigned long magic, size;
	int ret;

	/* VideoCore FDT was copied in PBL just above Barebox memory */
	saved_vc_fdt = (void *)(arm_mem_endmem_get());

	oftree = saved_vc_fdt;
	magic = be32_to_cpu(oftree->magic);

	if (magic == VIDEOCORE_FDT_ERROR) {
		if (oftree->totalsize)
			pr_err("there was an error copying fdt in pbl: %d\n",
					be32_to_cpu(oftree->totalsize));
		return;
	}

	if (magic != FDT_MAGIC) {
		pr_err("videocore fdt saved in pbl has invalid magic\n");
		return;
	}

	size = be32_to_cpu(oftree->totalsize);
	if (write_file("/vc.dtb", saved_vc_fdt, size)) {
		pr_err("failed to save videocore fdt to a file\n");
		return;
	}

	ret = rpi_vc_fdt_bootargs(saved_vc_fdt);
	if (ret) {
		pr_err("failed to extract bootargs from videocore fdt: %d\n",
									ret);
		return;
	}
}

static int rpi_devices_init(void)
{
	struct regulator *reg;

	rpi_add_led();
	bcm2835_register_fb();
	armlinux_set_architecture(MACH_TYPE_BCM2708);
	rpi_env_init();
	rpi_vc_fdt();

	reg = regulator_get_name("bcm2835_usb");
	if (IS_ERR(reg))
		return PTR_ERR(reg);

	regulator_enable(reg);

	return 0;
}
late_initcall(rpi_devices_init);
