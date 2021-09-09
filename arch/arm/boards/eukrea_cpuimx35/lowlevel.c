// SPDX-License-Identifier: GPL-2.0-or-later
// SPDX-FileCopyrightText: 2007 Sascha Hauer <s.hauer@pengutronix.de>, Pengutronix

#include <common.h>
#include <init.h>
#include <mach/imx35-regs.h>
#include <mach/imx-pll.h>
#include <mach/esdctl.h>
#include <asm/cache-l2x0.h>
#include <io.h>
#include <mach/imx-nand.h>
#include <asm/barebox-arm.h>
#include <asm/barebox-arm-head.h>
#include <asm/sections.h>
#include <asm-generic/memory_layout.h>
#include <asm/system.h>

void __bare_init __naked barebox_arm_reset_vector(uint32_t r0, uint32_t r1, uint32_t r2)
{
	uint32_t r, s;
	unsigned long ccm_base = MX35_CCM_BASE_ADDR;
	register uint32_t loops = 0x20000;

	arm_cpu_lowlevel_init();

	arm_setup_stack(MX35_IRAM_BASE_ADDR + MX35_IRAM_SIZE);

	r = get_cr();
	r |= CR_Z; /* Flow prediction (Z) */
	r |= CR_U; /* unaligned accesses  */
	r |= CR_FI; /* Low Int Latency     */

	__asm__ __volatile__("mrc p15, 0, %0, c1, c0, 1":"=r"(s));
	s |= 0x7;
	__asm__ __volatile__("mcr p15, 0, %0, c1, c0, 1" : : "r"(s));

	set_cr(r);

	r = 0;
	__asm__ __volatile__("mcr p15, 0, %0, c15, c2, 4" : : "r"(r));

	/*
	 * Branch predicition is now enabled.  Flush the BTAC to ensure a valid
	 * starting point.  Don't flush BTAC while it is disabled to avoid
	 * ARM1136 erratum 408023.
	 */
	__asm__ __volatile__("mcr p15, 0, %0, c7, c5, 6" : : "r"(r));

	/* invalidate I cache and D cache */
	__asm__ __volatile__("mcr p15, 0, %0, c7, c7, 0" : : "r"(r));

	/* invalidate TLBs */
	__asm__ __volatile__("mcr p15, 0, %0, c8, c7, 0" : : "r"(r));

	/* Drain the write buffer */
	__asm__ __volatile__("mcr p15, 0, %0, c7, c10, 4" : : "r"(r));

	/* Also setup the Peripheral Port Remap register inside the core */
	r = 0x40000015; /* start from AIPS 2GB region */
	__asm__ __volatile__("mcr p15, 0, %0, c15, c2, 4" : : "r"(r));

	/*
	 * End of ARM1136 init
	 */

	writel(0x003F4208, ccm_base + MX35_CCM_CCMR);

	/* Set MPLL , arm clock and ahb clock*/
	writel(MPCTL_PARAM_532, ccm_base + MX35_CCM_MPCTL);

	writel(PPCTL_PARAM_300, ccm_base + MX35_CCM_PPCTL);
	writel(0x00001000, ccm_base + MX35_CCM_PDR0);

	r = readl(ccm_base + MX35_CCM_CGR0);
	r |= 0x3 << MX35_CCM_CGR0_EPIT1_SHIFT;
	writel(r, ccm_base + MX35_CCM_CGR0);

	r = readl(ccm_base + MX35_CCM_CGR1);
	r |= 0x3 << MX35_CCM_CGR1_FEC_SHIFT;
	r |= 0x3 << MX35_CCM_CGR1_I2C1_SHIFT;
	r |= 0x3 << MX35_CCM_CGR1_IOMUX_SHIFT;
	writel(r, ccm_base + MX35_CCM_CGR1);

	/* enable watchdog asap */
	r = readl(ccm_base + MX35_CCM_CGR2);
	r |= 0x3 << MX35_CCM_CGR2_WDOG_SHIFT;
	writel(r, ccm_base + MX35_CCM_CGR2);

	r = readl(MX35_L2CC_BASE_ADDR + L2X0_AUX_CTRL);
	r |= 0x1000;
	writel(r, MX35_L2CC_BASE_ADDR + L2X0_AUX_CTRL);

	/* Skip SDRAM initialization if we run from RAM */
	r = get_pc();
	if (r > 0x80000000 && r < 0x90000000)
		goto out;

	/* Init Mobile DDR */
	writel(0x0000000E, MX35_ESDCTL_BASE_ADDR + IMX_ESDMISC);
	writel(0x00000004, MX35_ESDCTL_BASE_ADDR + IMX_ESDMISC);
	__asm__ volatile ("1:\n"
			"subs %0, %1, #1\n"
			"bne 1b":"=r" (loops):"0" (loops));

	writel(0x0009572B, MX35_ESDCTL_BASE_ADDR + IMX_ESDCFG0);
	writel(0x92220000, MX35_ESDCTL_BASE_ADDR + IMX_ESDCTL0);
	writeb(0xda, MX35_CSD0_BASE_ADDR + 0x400);
	writel(0xA2220000, MX35_ESDCTL_BASE_ADDR + IMX_ESDCTL0);
	writeb(0xda, MX35_CSD0_BASE_ADDR);
	writeb(0xda, MX35_CSD0_BASE_ADDR);
	writel(0xB2220000, MX35_ESDCTL_BASE_ADDR + IMX_ESDCTL0);
	writeb(0xda, MX35_CSD0_BASE_ADDR + 0x33);
	writeb(0xda, MX35_CSD0_BASE_ADDR + 0x2000000);
	writel(0x82228080, MX35_ESDCTL_BASE_ADDR + IMX_ESDCTL0);

	if (IS_ENABLED(CONFIG_ARCH_IMX_EXTERNAL_BOOT_NAND)) {
		/* Speed up NAND controller by adjusting the NFC divider */
		r = readl(MX35_CCM_BASE_ADDR + MX35_CCM_PDR4);
		r &= ~(0xf << 28);
		r |= 0x1 << 28;
		writel(r, MX35_CCM_BASE_ADDR + MX35_CCM_PDR4);

		imx35_barebox_boot_nand_external();
	}

out:
	imx35_barebox_entry(NULL);
}
