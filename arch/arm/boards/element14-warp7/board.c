// SPDX-License-Identifier: GPL-2.0-or-later
// SPDX-FileCopyrightText: 2017 Sascha Hauer, Pengutronix

#include <common.h>
#include <init.h>
#include <environment.h>
#include <mach/bbu.h>
#include <asm/armlinux.h>
#include <generated/mach-types.h>
#include <partition.h>
#include <mach/generic.h>
#include <linux/sizes.h>

static int warp7_devices_init(void)
{
	if (!of_machine_is_compatible("warp,imx7s-warp"))
		return 0;

	imx6_bbu_internal_mmc_register_handler("mmc", "/dev/mmc2.boot0.barebox",
					       BBU_HANDLER_FLAG_DEFAULT);

	return 0;
}
device_initcall(warp7_devices_init);
