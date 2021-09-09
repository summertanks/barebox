// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2018 Christian Hemp
 */

#include <common.h>
#include <firmware.h>
#include <linux/sizes.h>
#include <mach/generic.h>
#include <asm/barebox-arm-head.h>
#include <asm/barebox-arm.h>
#include <mach/imx8m-ccm-regs.h>
#include <mach/iomux-mx8mq.h>
#include <soc/imx8m/ddr.h>
#include <mach/xload.h>
#include <io.h>
#include <debug_ll.h>
#include <asm/cache.h>
#include <asm/sections.h>
#include <asm/mmu.h>
#include <mach/atf.h>
#include <mach/esdctl.h>

#include "ddr.h"

extern char __dtb_imx8mq_phytec_phycore_som_start[];

#define UART_PAD_CTRL	MUX_PAD_CTRL(PAD_CTL_DSE_3P3V_45_OHM)

static void setup_uart(void)
{
	void __iomem *uart = IOMEM(MX8M_UART1_BASE_ADDR);

	imx8m_early_setup_uart_clock();

	imx8mq_setup_pad(IMX8MQ_PAD_UART1_TXD__UART1_TX | UART_PAD_CTRL);

	imx8m_uart_setup(uart);

	pbl_set_putc(imx_uart_putc, uart);

	putc_ll('>');
}

static void phytec_imx8mq_som_sram_setup(void)
{
	enum bootsource src = BOOTSOURCE_UNKNOWN;
	int instance = BOOTSOURCE_INSTANCE_UNKNOWN;
	int ret = -ENOTSUPP;

	ddr_init();

	imx8mq_get_boot_source(&src, &instance);

	if (src == BOOTSOURCE_MMC)
		ret = imx8m_esdhc_load_image(instance, true);

	BUG_ON(ret);
}

static __noreturn noinline void phytec_phycore_imx8mq_start(void)
{
	setup_uart();

	if (get_pc() < MX8MQ_DDR_CSD1_BASE_ADDR) {
		/*
		 * We assume that we were just loaded by MaskROM into
		 * SRAM if we are not running from DDR. We also assume
		 * that means DDR needs to be initialized for the
		 * first time.
		 */
		phytec_imx8mq_som_sram_setup();
	}
	/*
	 * Straight from the power-on we are at EL3, so the following
	 * code _will_ load and jump to ATF.
	 *
	 * However when we are re-executed upon exit from ATF's
	 * initialization routine, it is EL2 which means we'll skip
	 * loadting ATF blob again
	 */
	if (current_el() == 3) {
		const u8 *bl31;
		size_t bl31_size;

		get_builtin_firmware(imx8mq_bl31_bin, &bl31, &bl31_size);
		imx8mq_atf_load_bl31(bl31, bl31_size);
	}

	/*
	 * Standard entry we hit once we initialized both DDR and ATF
	 */
	imx8mq_barebox_entry(__dtb_imx8mq_phytec_phycore_som_start);
}

/*
 * Power-on execution flow of start_phytec_phycore_imx8mq() might not be
 * obvious for a very first read, so here's, hopefully helpful,
 * summary:
 *
 * 1. MaskROM uploads PBL into OCRAM and that's where this function is
 *    executed for the first time
 *
 * 2. DDR is initialized and full i.MX image is loaded to the
 *    beginning of RAM
 *
 * 3. start_phytec_phycore_imx8mq, now in RAM, is executed again
 *
 * 4. BL31 blob is uploaded to OCRAM and the control is transfer to it
 *
 * 5. BL31 exits EL3 into EL2 at address MX8MQ_ATF_BL33_BASE_ADDR,
 *    executing start_phytec_phycore_imx8mq() the third time
 *
 * 6. Standard barebox boot flow continues
 */
ENTRY_FUNCTION(start_phytec_phycore_imx8mq, r0, r1, r2)
{
	imx8mq_cpu_lowlevel_init();
	relocate_to_current_adr();
	setup_c();

	phytec_phycore_imx8mq_start();
}
