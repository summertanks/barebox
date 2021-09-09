/* SPDX-License-Identifier: GPL-2.0-only */
/*
 *  Atheros AR71XX/AR724X/AR913X SoC register definitions
 *
 *  Copyright (C) 2010-2011 Jaiganesh Narayanan <jnarayanan@atheros.com>
 *  Copyright (C) 2008-2010 Gabor Juhos <juhosg@openwrt.org>
 *  Copyright (C) 2008 Imre Kaloz <kaloz@openwrt.org>
 *
 *  Parts of this file are based on Atheros' 2.6.15/2.6.31 BSP
 */

#ifndef __ASM_MACH_AR71XX_REGS_H
#define __ASM_MACH_AR71XX_REGS_H

#ifndef __ASSEMBLER__
#include <linux/bitops.h>
#else
#define BIT(nr)  (1 << (nr))
#endif

#define AR71XX_APB_BASE		0x18000000

#define AR71XX_DDR_CTRL_BASE	(AR71XX_APB_BASE + 0x00000000)
#define AR71XX_DDR_CTRL_SIZE	0x100
#define AR71XX_GPIO_BASE	(AR71XX_APB_BASE + 0x00040000)
#define AR71XX_GPIO_SIZE	0x100
#define AR71XX_PLL_BASE		(AR71XX_APB_BASE + 0x00050000)
#define AR71XX_PLL_SIZE		0x100
#define AR71XX_RESET_BASE	(AR71XX_APB_BASE + 0x00060000)
#define AR71XX_RESET_SIZE	0x100
#define AR71XX_RTC_BASE		(AR71XX_APB_BASE + 0x00107000)
#define AR71XX_RTC_SIZE		0x100

#define AR933X_UART_BASE	(AR71XX_APB_BASE + 0x00020000)
#define AR933X_UART_SIZE	0x14

#define AR934X_UART0_BASE	(AR71XX_APB_BASE + 0x00020000)
#define AR934X_UART0_SIZE	0x18
#define AR934X_UART0_SHIFT	2

/* WASP BootStrap Register */
#define WASP_BOOTSTRAP_REG		(AR71XX_RESET_BASE + 0xb0)
#define WASP_REF_CLK_25			(1 << 4) /* 0 - 25MHz	1 - 40 MHz */
#define WASP_RAM_TYPE(a)		((a) & 0x3)

/*
 * RTC block
 */
#define AR933X_RTC_REG_RESET		0x40
#define AR933X_RTC_REG_STATUS		0x44
#define AR933X_RTC_REG_DERIVED		0x48
#define AR933X_RTC_REG_FORCE_WAKE	0x4c
#define AR933X_RTC_REG_INT_CAUSE	0x50
#define AR933X_RTC_REG_CAUSE_CLR	0x50
#define AR933X_RTC_REG_INT_ENABLE	0x54
#define AR933X_RTC_REG_INT_MASKE	0x58

/*
 * DDR_CTRL block
 */
#define AR933X_DDR_CONFIG		0x00
#define AR933X_DDR_CONFIG2		0x04
#define AR933X_DDR_MODE			0x08
#define AR933X_DDR_EXT_MODE		0x0c
#define AR933X_DDR_CTRL			0x10
#define AR933X_DDR_REFRESH		0x14
#define AR933X_DDR_RD_DATA		0x18
#define AR933X_DDR_TAP_CTRL0		0x1c
#define AR933X_DDR_TAP_CTRL1		0x20
#define AR933X_DDR_TAP_CTRL1		0x20

#define AR933X_DDR_DDR_DDR2_CONFIG	0x8c
#define AR933X_DDR_DDR_EMR2		0x90
#define AR933X_DDR_DDR_EMR3		0x94

/*
 * GPIO block
 */
#define AR71XX_GPIO_REG_OE		0x00
#define AR71XX_GPIO_REG_IN		0x04
#define AR71XX_GPIO_REG_OUT		0x08
#define AR71XX_GPIO_REG_SET		0x0c
#define AR71XX_GPIO_REG_CLEAR		0x10
#define AR71XX_GPIO_REG_INT_MODE	0x14
#define AR71XX_GPIO_REG_INT_TYPE	0x18
#define AR71XX_GPIO_REG_INT_POLARITY	0x1c
#define AR71XX_GPIO_REG_INT_PENDING	0x20
#define AR71XX_GPIO_REG_INT_ENABLE	0x24
#define AR71XX_GPIO_REG_FUNC		0x28
/* Warning! GPIO_FUNC[15] must be written with 1 */
#define AR933X_GPIO_FUNC_RSRV15			BIT(15)
#define AR933X_GPIO_FUNC_UART_EN		BIT(1)

/*
 * PLL block
 */
#define AR933X_PLL_CPU_CONFIG_REG	0x00
#define AR933X_PLL_CPU_CONFIG2_REG	0x04
#define AR933X_PLL_CLOCK_CTRL_REG	0x08
#define AR933X_PLL_DITHER_FRAC_REG	0x10
#define AR933X_PLL_DITHER_REG		0x14
#define AR933X_ETHSW_CLOCK_CONTROL_REG	0x24
#define AR933X_ETH_XMII_CONTROL_REG	0x2c

#define AR933X_PLL_CPU_CONFIG_NINT_SHIFT	10
#define AR933X_PLL_CPU_CONFIG_NINT_MASK		0x3f
#define AR933X_PLL_CPU_CONFIG_REFDIV_SHIFT	16
#define AR933X_PLL_CPU_CONFIG_REFDIV_MASK	0x1f
#define AR933X_PLL_CPU_CONFIG_OUTDIV_SHIFT	23
#define AR933X_PLL_CPU_CONFIG_OUTDIV_MASK	0x7
#define AR933X_PLL_CPU_CONFIG_PLLPWD		BIT(30)

#define AR933X_PLL_CLOCK_CTRL_BYPASS		BIT(2)
#define AR933X_PLL_CLOCK_CTRL_CPU_DIV_SHIFT	5
#define AR933X_PLL_CLOCK_CTRL_CPU_DIV_MASK	0x3
#define AR933X_PLL_CLOCK_CTRL_DDR_DIV_SHIFT	10
#define AR933X_PLL_CLOCK_CTRL_DDR_DIV_MASK	0x3
#define AR933X_PLL_CLOCK_CTRL_AHB_DIV_SHIFT	15
#define AR933X_PLL_CLOCK_CTRL_AHB_DIV_MASK	0x7

/*
 * RESET block
 */
#define AR933X_RESET_REG_RESET_MODULE		0x1c
#define AR933X_RESET_REG_BOOTSTRAP		0xac

#define AR933X_RESET_GE1_MDIO           BIT(23)
#define AR933X_RESET_GE0_MDIO           BIT(22)
#define AR933X_RESET_GE1_MAC            BIT(13)
#define AR933X_RESET_WMAC               BIT(11)
#define AR933X_RESET_GE0_MAC            BIT(9)
#define AR933X_RESET_SWITCH             BIT(8)
#define AR933X_RESET_USB_HOST           BIT(5)
#define AR933X_RESET_USB_PHY            BIT(4)
#define AR933X_RESET_USBSUS_OVERRIDE    BIT(3)

#define AR71XX_RESET_FULL_CHIP		BIT(24)

#define AR933X_BOOTSTRAP_MEM_TYPE	BIT(13)
#define AR933X_BOOTSTRAP_REF_CLK_40	BIT(0)

#endif /* __ASM_MACH_AR71XX_REGS_H */