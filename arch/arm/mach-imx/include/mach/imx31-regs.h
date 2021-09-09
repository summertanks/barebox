/* SPDX-License-Identifier: GPL-2.0-or-later */
/* SPDX-FileCopyrightText: 2007 Sascha Hauer <s.hauer@pengutronix.de>, Pengutronix */

#ifndef __ASM_ARCH_MX31_REGS_H
#define __ASM_ARCH_MX31_REGS_H

#include <linux/sizes.h>

#define MX31_IRAM_BASE_ADDR		0x1fffc000
#define MX31_IRAM_SIZE			0x00004000

#define MX31_AIPS1_BASE_ADDR		0x43f00000
#define MX31_AIPS1_SIZE			SZ_1M
#define MX31_MAX_BASE_ADDR			(MX31_AIPS1_BASE_ADDR + 0x04000)
#define MX31_EVTMON_BASE_ADDR			(MX31_AIPS1_BASE_ADDR + 0x08000)
#define MX31_CLKCTL_BASE_ADDR			(MX31_AIPS1_BASE_ADDR + 0x0c000)
#define MX31_ETB_SLOT4_BASE_ADDR		(MX31_AIPS1_BASE_ADDR + 0x10000)
#define MX31_ETB_SLOT5_BASE_ADDR		(MX31_AIPS1_BASE_ADDR + 0x14000)
#define MX31_ECT_CTIO_BASE_ADDR			(MX31_AIPS1_BASE_ADDR + 0x18000)
#define MX31_I2C1_BASE_ADDR			(MX31_AIPS1_BASE_ADDR + 0x80000)
#define MX31_I2C3_BASE_ADDR			(MX31_AIPS1_BASE_ADDR + 0x84000)
#define MX31_USB_BASE_ADDR			(MX31_AIPS1_BASE_ADDR + 0x88000)
#define MX31_USB_OTG_BASE_ADDR			(MX31_USB_BASE_ADDR + 0x0000)
#define MX31_USB_HS1_BASE_ADDR			(MX31_USB_BASE_ADDR + 0x0200)
#define MX31_USB_HS2_BASE_ADDR			(MX31_USB_BASE_ADDR + 0x0400)
#define MX31_ATA_BASE_ADDR			(MX31_AIPS1_BASE_ADDR + 0x8c000)
#define MX31_UART1_BASE_ADDR			(MX31_AIPS1_BASE_ADDR + 0x90000)
#define MX31_UART2_BASE_ADDR			(MX31_AIPS1_BASE_ADDR + 0x94000)
#define MX31_I2C2_BASE_ADDR			(MX31_AIPS1_BASE_ADDR + 0x98000)
#define MX31_OWIRE_BASE_ADDR			(MX31_AIPS1_BASE_ADDR + 0x9c000)
#define MX31_SSI1_BASE_ADDR			(MX31_AIPS1_BASE_ADDR + 0xa0000)
#define MX31_CSPI1_BASE_ADDR			(MX31_AIPS1_BASE_ADDR + 0xa4000)
#define MX31_KPP_BASE_ADDR			(MX31_AIPS1_BASE_ADDR + 0xa8000)
#define MX31_IOMUXC_BASE_ADDR			(MX31_AIPS1_BASE_ADDR + 0xac000)
#define MX31_UART4_BASE_ADDR			(MX31_AIPS1_BASE_ADDR + 0xb0000)
#define MX31_UART5_BASE_ADDR			(MX31_AIPS1_BASE_ADDR + 0xb4000)
#define MX31_ECT_IP1_BASE_ADDR			(MX31_AIPS1_BASE_ADDR + 0xb8000)
#define MX31_ECT_IP2_BASE_ADDR			(MX31_AIPS1_BASE_ADDR + 0xbc000)

#define MX31_SPBA0_BASE_ADDR		0x50000000
#define MX31_SPBA0_SIZE			SZ_1M
#define MX31_SDHC1_BASE_ADDR			(MX31_SPBA0_BASE_ADDR + 0x04000)
#define MX31_SDHC2_BASE_ADDR			(MX31_SPBA0_BASE_ADDR + 0x08000)
#define MX31_UART3_BASE_ADDR			(MX31_SPBA0_BASE_ADDR + 0x0c000)
#define MX31_CSPI2_BASE_ADDR			(MX31_SPBA0_BASE_ADDR + 0x10000)
#define MX31_SSI2_BASE_ADDR			(MX31_SPBA0_BASE_ADDR + 0x14000)
#define MX31_SIM1_BASE_ADDR			(MX31_SPBA0_BASE_ADDR + 0x18000)
#define MX31_IIM_BASE_ADDR			(MX31_SPBA0_BASE_ADDR + 0x1c000)
#define MX31_ATA_DMA_BASE_ADDR			(MX31_SPBA0_BASE_ADDR + 0x20000)
#define MX31_MSHC1_BASE_ADDR			(MX31_SPBA0_BASE_ADDR + 0x24000)
#define MX31_SPBA_CTRL_BASE_ADDR		(MX31_SPBA0_BASE_ADDR + 0x3c000)

#define MX31_AIPS2_BASE_ADDR		0x53f00000
#define MX31_AIPS2_SIZE			SZ_1M
#define MX31_CCM_BASE_ADDR			(MX31_AIPS2_BASE_ADDR + 0x80000)
#define MX31_CSPI3_BASE_ADDR			(MX31_AIPS2_BASE_ADDR + 0x84000)
#define MX31_FIRI_BASE_ADDR			(MX31_AIPS2_BASE_ADDR + 0x8c000)
#define MX31_GPT1_BASE_ADDR			(MX31_AIPS2_BASE_ADDR + 0x90000)
#define MX31_EPIT1_BASE_ADDR			(MX31_AIPS2_BASE_ADDR + 0x94000)
#define MX31_EPIT2_BASE_ADDR			(MX31_AIPS2_BASE_ADDR + 0x98000)
#define MX31_GPIO3_BASE_ADDR			(MX31_AIPS2_BASE_ADDR + 0xa4000)
#define MX31_SCC_BASE_ADDR			(MX31_AIPS2_BASE_ADDR + 0xac000)
#define MX31_SCM_BASE_ADDR			(MX31_AIPS2_BASE_ADDR + 0xae000)
#define MX31_SMN_BASE_ADDR			(MX31_AIPS2_BASE_ADDR + 0xaf000)
#define MX31_RNGA_BASE_ADDR			(MX31_AIPS2_BASE_ADDR + 0xb0000)
#define MX31_IPU_CTRL_BASE_ADDR			(MX31_AIPS2_BASE_ADDR + 0xc0000)
#define MX31_AUDMUX_BASE_ADDR			(MX31_AIPS2_BASE_ADDR + 0xc4000)
#define MX31_MPEG4_ENC_BASE_ADDR		(MX31_AIPS2_BASE_ADDR + 0xc8000)
#define MX31_GPIO1_BASE_ADDR			(MX31_AIPS2_BASE_ADDR + 0xcc000)
#define MX31_GPIO2_BASE_ADDR			(MX31_AIPS2_BASE_ADDR + 0xd0000)
#define MX31_SDMA_BASE_ADDR			(MX31_AIPS2_BASE_ADDR + 0xd4000)
#define MX31_RTC_BASE_ADDR			(MX31_AIPS2_BASE_ADDR + 0xd8000)
#define MX31_WDOG_BASE_ADDR			(MX31_AIPS2_BASE_ADDR + 0xdc000)
#define MX31_PWM_BASE_ADDR			(MX31_AIPS2_BASE_ADDR + 0xe0000)
#define MX31_RTIC_BASE_ADDR			(MX31_AIPS2_BASE_ADDR + 0xec000)

#define MX31_ROMP_BASE_ADDR		0x60000000
#define MX31_ROMP_SIZE			SZ_1M

#define MX31_AVIC_BASE_ADDR		0x68000000
#define MX31_AVIC_SIZE			SZ_1M

#define MX31_IPU_MEM_BASE_ADDR		0x70000000
#define MX31_CSD0_BASE_ADDR		0x80000000
#define MX31_CSD1_BASE_ADDR		0x90000000

#define MX31_CS0_BASE_ADDR		0xa0000000
#define MX31_CS0_SIZE			SZ_128M

#define MX31_CS1_BASE_ADDR		0xa8000000
#define MX31_CS1_SIZE			SZ_128M

#define MX31_CS2_BASE_ADDR		0xb0000000
#define MX31_CS2_SIZE			SZ_32M

#define MX31_CS3_BASE_ADDR		0xb2000000
#define MX31_CS3_SIZE			SZ_32M

#define MX31_CS4_BASE_ADDR		0xb4000000
#define MX31_CS4_SIZE			SZ_32M

#define MX31_CS5_BASE_ADDR		0xb6000000
#define MX31_CS5_SIZE			SZ_32M

#define MX31_X_MEMC_BASE_ADDR		0xb8000000
#define MX31_X_MEMC_SIZE		SZ_64K
#define MX31_NFC_BASE_ADDR			(MX31_X_MEMC_BASE_ADDR + 0x0000)
#define MX31_ESDCTL_BASE_ADDR			(MX31_X_MEMC_BASE_ADDR + 0x1000)
#define MX31_WEIM_BASE_ADDR			(MX31_X_MEMC_BASE_ADDR + 0x2000)
#define MX31_M3IF_BASE_ADDR			(MX31_X_MEMC_BASE_ADDR + 0x3000)
#define MX31_EMI_CTL_BASE_ADDR			(MX31_X_MEMC_BASE_ADDR + 0x4000)
#define MX31_PCMCIA_CTL_BASE_ADDR		MX31_EMI_CTL_BASE_ADDR

#define MX31_WEIM_CSCRx_BASE_ADDR(cs)	(MX31_WEIM_BASE_ADDR + (cs) * 0x10)
#define MX31_WEIM_CSCRxU(cs)			(MX31_WEIM_CSCRx_BASE_ADDR(cs))
#define MX31_WEIM_CSCRxL(cs)			(MX31_WEIM_CSCRx_BASE_ADDR(cs) + 0x4)
#define MX31_WEIM_CSCRxA(cs)			(MX31_WEIM_CSCRx_BASE_ADDR(cs) + 0x8)

#define MX31_PCMCIA_MEM_BASE_ADDR	0xbc000000

/*
 * Clock Controller Module (CCM)
 */
#define MX31_CCM_CCMR	0x00
#define MX31_CCM_PDR0	0x04
#define MX31_CCM_PDR1	0x08
#define MX31_CCM_RCSR	0x0c
#define MX31_CCM_MPCTL	0x10
#define MX31_CCM_UPCTL	0x14
#define MX31_CCM_SPCTL	0x18
#define MX31_CCM_COSR	0x1C

#define MX31_CCMR_MDS	(1 << 7)
#define MX31_CCMR_SBYCS	(1 << 4)
#define MX31_CCMR_MPE	(1 << 3)
#define MX31_CCMR_PRCS_MASK	(3 << 1)
#define MX31_CCMR_FPM	(1 << 1)
#define MX31_CCMR_CKIH	(2 << 1)

#define MX31_RCSR_NFMS	(1 << 30)

#define MX31_PDR0_CSI_PODF(x)	(((x) & 0x1ff) << 23)
#define MX31_PDR0_PER_PODF(x)	(((x) & 0x1f) << 16)
#define MX31_PDR0_HSP_PODF(x)	(((x) & 0x7) << 11)
#define MX31_PDR0_NFC_PODF(x)	(((x) & 0x7) << 8)
#define MX31_PDR0_IPG_PODF(x)	(((x) & 0x3) << 6)
#define MX31_PDR0_MAX_PODF(x)	(((x) & 0x7) << 3)
#define MX31_PDR0_MCU_PODF(x)	((x) & 0x7)

#define MX31_IOMUXC_GPR	(MX31_IOMUXC_BASE_ADDR + 0x8)
#define MX31_IOMUXC_SW_MUX_CTL(x)	(MX31_IOMUXC_BASE_ADDR + 0xc + (x) * 4)
#define MX31_IOMUXC_SW_PAD_CTL(x)	(MX31_IOMUXC_BASE_ADDR + 0x154 + (x) * 4)

/*
 * Signal Multiplexing (IOMUX)
 */

/* bits in the SW_MUX_CTL registers */
#define MX31_MUX_CTL_OUT_GPIO_DR	(0 << 4)
#define MX31_MUX_CTL_OUT_FUNC		(1 << 4)
#define MX31_MUX_CTL_OUT_ALT1		(2 << 4)
#define MX31_MUX_CTL_OUT_ALT2		(3 << 4)
#define MX31_MUX_CTL_OUT_ALT3		(4 << 4)
#define MX31_MUX_CTL_OUT_ALT4		(5 << 4)
#define MX31_MUX_CTL_OUT_ALT5		(6 << 4)
#define MX31_MUX_CTL_OUT_ALT6		(7 << 4)
#define MX31_MUX_CTL_IN_NONE		(0 << 0)
#define MX31_MUX_CTL_IN_GPIO		(1 << 0)
#define MX31_MUX_CTL_IN_FUNC		(2 << 0)
#define MX31_MUX_CTL_IN_ALT1		(4 << 0)
#define MX31_MUX_CTL_IN_ALT2		(8 << 0)

#define MX31_MUX_CTL_FUNC	(MX31_MUX_CTL_OUT_FUNC | MX31_MUX_CTL_IN_FUNC)
#define MX31_MUX_CTL_ALT1	(MX31_MUX_CTL_OUT_ALT1 | MX31_MUX_CTL_IN_ALT1)
#define MX31_MUX_CTL_ALT2	(MX31_MUX_CTL_OUT_ALT2 | MX31_MUX_CTL_IN_ALT2)
#define MX31_MUX_CTL_GPIO	(MX31_MUX_CTL_OUT_GPIO_DR | MX31_MUX_CTL_IN_GPIO)

#endif /* __ASM_ARCH_MX31_REGS_H */
