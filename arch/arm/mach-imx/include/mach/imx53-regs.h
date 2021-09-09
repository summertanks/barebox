#ifndef __MACH_IMX53_REGS_H
#define __MACH_IMX53_REGS_H

#include <linux/sizes.h>

#define MX53_IROM_BASE_ADDR	0x0

#define MX53_IRAM_BASE_ADDR	0xF8000000
#define MX53_IRAM_SIZE		SZ_128K

#define MX53_SATA_BASE_ADDR	0x10000000

#define MX53_IPU_BASE_ADDR	0x18000000
/*
 * SPBA global module enabled #0
 */
#define MX53_SPBA0_BASE_ADDR		0x50000000
#define MX53_SPBA0_SIZE		SZ_1M

#define MX53_ESDHC1_BASE_ADDR	(MX53_SPBA0_BASE_ADDR + 0x00004000)
#define MX53_ESDHC2_BASE_ADDR	(MX53_SPBA0_BASE_ADDR + 0x00008000)
#define MX53_UART3_BASE_ADDR		(MX53_SPBA0_BASE_ADDR + 0x0000C000)
#define MX53_ECSPI1_BASE_ADDR		(MX53_SPBA0_BASE_ADDR + 0x00010000)
#define MX53_SSI2_BASE_ADDR		(MX53_SPBA0_BASE_ADDR + 0x00014000)
#define MX53_ESDHC3_BASE_ADDR	(MX53_SPBA0_BASE_ADDR + 0x00020000)
#define MX53_ESDHC4_BASE_ADDR	(MX53_SPBA0_BASE_ADDR + 0x00024000)
#define MX53_SPDIF_BASE_ADDR		(MX53_SPBA0_BASE_ADDR + 0x00028000)
#define MX53_ASRC_BASE_ADDR		(MX53_SPBA0_BASE_ADDR + 0x0002C000)
#define MX53_ATA_DMA_BASE_ADDR	(MX53_SPBA0_BASE_ADDR + 0x00030000)
#define MX53_SLIM_DMA_BASE_ADDR	(MX53_SPBA0_BASE_ADDR + 0x00034000)
#define MX53_HSI2C_DMA_BASE_ADDR	(MX53_SPBA0_BASE_ADDR + 0x00038000)
#define MX53_SPBA_CTRL_BASE_ADDR	(MX53_SPBA0_BASE_ADDR + 0x0003C000)

/*
 * AIPS 1
 */
#define MX53_AIPS1_BASE_ADDR 	0x53F00000
#define MX53_AIPS1_SIZE		SZ_1M

#define MX53_OTG_BASE_ADDR	(MX53_AIPS1_BASE_ADDR + 0x00080000)
#define MX53_GPIO1_BASE_ADDR	(MX53_AIPS1_BASE_ADDR + 0x00084000)
#define MX53_GPIO2_BASE_ADDR	(MX53_AIPS1_BASE_ADDR + 0x00088000)
#define MX53_GPIO3_BASE_ADDR	(MX53_AIPS1_BASE_ADDR + 0x0008C000)
#define MX53_GPIO4_BASE_ADDR	(MX53_AIPS1_BASE_ADDR + 0x00090000)
#define MX53_KPP_BASE_ADDR	(MX53_AIPS1_BASE_ADDR + 0x00094000)
#define MX53_WDOG1_BASE_ADDR	(MX53_AIPS1_BASE_ADDR + 0x00098000)
#define MX53_WDOG2_BASE_ADDR	(MX53_AIPS1_BASE_ADDR + 0x0009C000)
#define MX53_GPT1_BASE_ADDR	(MX53_AIPS1_BASE_ADDR + 0x000A0000)
#define MX53_SRTC_BASE_ADDR	(MX53_AIPS1_BASE_ADDR + 0x000A4000)
#define MX53_IOMUXC_BASE_ADDR	(MX53_AIPS1_BASE_ADDR + 0x000A8000)
#define MX53_EPIT1_BASE_ADDR	(MX53_AIPS1_BASE_ADDR + 0x000AC000)
#define MX53_EPIT2_BASE_ADDR	(MX53_AIPS1_BASE_ADDR + 0x000B0000)
#define MX53_PWM1_BASE_ADDR	(MX53_AIPS1_BASE_ADDR + 0x000B4000)
#define MX53_PWM2_BASE_ADDR	(MX53_AIPS1_BASE_ADDR + 0x000B8000)
#define MX53_UART1_BASE_ADDR	(MX53_AIPS1_BASE_ADDR + 0x000BC000)
#define MX53_UART2_BASE_ADDR	(MX53_AIPS1_BASE_ADDR + 0x000C0000)
#define MX53_SRC_BASE_ADDR	(MX53_AIPS1_BASE_ADDR + 0x000D0000)
#define MX53_CCM_BASE_ADDR	(MX53_AIPS1_BASE_ADDR + 0x000D4000)
#define MX53_GPC_BASE_ADDR	(MX53_AIPS1_BASE_ADDR + 0x000D8000)
#define MX53_GPIO5_BASE_ADDR	(MX53_AIPS1_BASE_ADDR + 0x000DC000)
#define MX53_GPIO6_BASE_ADDR	(MX53_AIPS1_BASE_ADDR + 0x000E0000)
#define MX53_GPIO7_BASE_ADDR	(MX53_AIPS1_BASE_ADDR + 0x000E4000)
#define MX53_ATA_BASE_ADDR	(MX53_AIPS1_BASE_ADDR + 0x000E8000)
#define MX53_I2C3_BASE_ADDR	(MX53_AIPS1_BASE_ADDR + 0x000EC000)
#define MX53_UART4_BASE_ADDR	(MX53_AIPS1_BASE_ADDR + 0x000F0000)

/*
 * AIPS 2
 */
#define MX53_AIPS2_BASE_ADDR		0x63F00000
#define MX53_AIPS2_SIZE			SZ_1M

#define MX53_PLL1_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x00080000)
#define MX53_PLL2_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x00084000)
#define MX53_PLL3_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x00088000)
#define MX53_PLL4_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x0008C000)
#define MX53_UART5_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x00090000)
#define MX53_AHBMAX_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x00094000)
#define MX53_IIM_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x00098000)
#define MX53_CSU_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x0009C000)
#define MX53_ARM_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x000A0000)
#define MX53_OWIRE_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x000A4000)
#define MX53_FIRI_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x000A8000)
#define MX53_ECSPI2_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x000AC000)
#define MX53_SDMA_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x000B0000)
#define MX53_SCC_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x000B4000)
#define MX53_ROMCP_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x000B8000)
#define MX53_RTIC_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x000BC000)
#define MX53_CSPI_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x000C0000)
#define MX53_I2C2_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x000C4000)
#define MX53_I2C1_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x000C8000)
#define MX53_SSI1_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x000CC000)
#define MX53_AUDMUX_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x000D0000)
#define MX53_RTC_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x000D4000)
#define MX53_M4IF_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x000D8000)
#define MX53_ESDCTL_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x000D9000)
#define MX53_WEIM_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x000DA000)
#define MX53_NFC_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x000DB000)
#define MX53_EMI_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x000DBF00)
#define MX53_MIPI_HSC_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x000DC000)
#define MX53_MLB_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x000E4000)
#define MX53_SSI3_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x000E8000)
#define MX53_FEC_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x000EC000)
#define MX53_TVE_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x000F0000)
#define MX53_VPU_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x000F4000)
#define MX53_SAHARA_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x000F8000)
#define MX53_PTP_BASE_ADDR	(MX53_AIPS2_BASE_ADDR + 0x000FC000)

#define MX53_NFC_AXI_BASE_ADDR	0xF7FF0000

/*
 * Memory regions and CS
 */
#define MX53_CSD0_BASE_ADDR		0x70000000
#define MX53_CSD1_BASE_ADDR		0xB0000000
#define MX53_CS0_BASE_ADDR		0xF0000000
#define MX53_CS1_32MB_BASE_ADDR		0xF2000000
#define MX53_CS1_64MB_BASE_ADDR		0xF4000000
#define MX53_CS2_64MB_BASE_ADDR		0xF4000000
#define MX53_CS2_96MB_BASE_ADDR		0xF6000000
#define MX53_CS3_BASE_ADDR		0xF6000000

#endif /* __MACH_IMX53_REGS_H */

