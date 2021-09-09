// SPDX-License-Identifier: GPL-2.0-or-later
// SPDX-FileCopyrightText: 2017 Sascha Hauer, Pengutronix

#include <common.h>
#include <init.h>
#include <mach/bbu.h>
#include <common.h>
#include <driver.h>
#include <bbu.h>
#include <envfs.h>

static int caisteal_imx6ul_init(void)
{
	if (!of_machine_is_compatible("fsl,imx6ul-caisteal"))
		return 0;

	defaultenv_append_directory(defaultenv_caisteal_imx6ul);
	imx6_bbu_internal_spi_i2c_register_handler("spiflash","/dev/m25p0.barebox", BBU_HANDLER_FLAG_DEFAULT);

	barebox_set_hostname("caisteal-imx6ul");

	return 0;
}
device_initcall(caisteal_imx6ul_init);


