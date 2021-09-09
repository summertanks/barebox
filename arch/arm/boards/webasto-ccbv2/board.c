// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright (C) 2019 Rouven Czerwinski, Pengutronix
 */

#include <common.h>
#include <init.h>
#include <mach/generic.h>
#include <mach/bbu.h>
#include <of.h>
#include <string.h>

#include "ccbv2.h"

static int ccbv2_probe(struct device_d *dev)
{
	struct device_node *overlay;
	struct fdt_header *fdt;
	int ret;

	/* the bootloader is stored in one of the two boot partitions */
	imx6_bbu_internal_mmcboot_register_handler("emmc", "/dev/mmc1",
			BBU_HANDLER_FLAG_DEFAULT);

	barebox_set_hostname("weabsto-ccbv2");

	if(!IS_ENABLED(CONFIG_FIRMWARE_CCBV2_OPTEE))
		return 0;

	fdt = (void*)OPTEE_OVERLAY_LOCATION;
	overlay = of_unflatten_dtb(fdt, INT_MAX);

	if (IS_ERR(overlay))
		return PTR_ERR(overlay);

	ret = of_register_overlay(overlay);
	if (ret) {
		printf("cannot apply oftree overlay: %s\n", strerror(-ret));
		goto err;
	}

	return 0;
err:
	of_delete_node(overlay);
	return ret;

}

static const struct of_device_id ccbv2_of_match[] = {
	{ .compatible = "webasto,imx6ul-ccbv2" },
	{ /* sentinel */ },
};

static struct driver_d ccbv2_board_driver = {
	.name = "board-imx6ul-ccbv2",
	.probe = ccbv2_probe,
	.of_compatible = ccbv2_of_match,
};
postcore_platform_driver(ccbv2_board_driver);
