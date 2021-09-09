#ifndef __MACH_IMX8MQ_REGS_H
#define __MACH_IMX8MQ_REGS_H

#include <mach/imx8m-regs.h>

#define MX8MQ_M4_BOOTROM_BASE_ADDR	0x007E0000

#define MX8MQ_SAI1_BASE_ADDR		0x30010000
#define MX8MQ_SAI6_BASE_ADDR		0x30030000
#define MX8MQ_SAI5_BASE_ADDR		0x30040000
#define MX8MQ_SAI4_BASE_ADDR		0x30050000
#define MX8MQ_SPBA2_BASE_ADDR		0x300F0000
#define MX8MQ_AIPS1_BASE_ADDR		0x301F0000
#define MX8MQ_GPIO1_BASE_ADDR		0X30200000
#define MX8MQ_GPIO2_BASE_ADDR		0x30210000
#define MX8MQ_GPIO3_BASE_ADDR		0x30220000
#define MX8MQ_GPIO4_BASE_ADDR		0x30230000
#define MX8MQ_GPIO5_BASE_ADDR		0x30240000
#define MX8MQ_ANA_TSENSOR_BASE_ADDR	0x30260000
#define MX8MQ_ANA_OSC_BASE_ADDR		0x30270000
#define MX8MQ_WDOG1_BASE_ADDR		0x30280000
#define MX8MQ_WDOG2_BASE_ADDR		0x30290000
#define MX8MQ_WDOG3_BASE_ADDR		0x302A0000
#define MX8MQ_SDMA2_BASE_ADDR		0x302C0000
#define MX8MQ_GPT1_BASE_ADDR		0x302D0000
#define MX8MQ_GPT2_BASE_ADDR		0x302E0000
#define MX8MQ_GPT3_BASE_ADDR		0x302F0000
#define MX8MQ_ROMCP_BASE_ADDR		0x30310000
#define MX8MQ_LCDIF_BASE_ADDR		0x30320000
#define MX8MQ_IOMUXC_BASE_ADDR		0x30330000
#define MX8MQ_IOMUXC_GPR_BASE_ADDR	0x30340000
#define MX8MQ_OCOTP_BASE_ADDR		0x30350000
#define MX8MQ_ANATOP_BASE_ADDR		0x30360000
#define MX8MQ_SNVS_HP_BASE_ADDR		0x30370000
#define MX8MQ_CCM_BASE_ADDR		0x30380000
#define MX8MQ_SRC_BASE_ADDR		0x30390000
#define MX8MQ_GPC_BASE_ADDR		0x303A0000
#define MX8MQ_SEMAPHORE1_BASE_ADDR	0x303B0000
#define MX8MQ_SEMAPHORE2_BASE_ADDR	0x303C0000
#define MX8MQ_RDC_BASE_ADDR		0x303D0000
#define MX8MQ_CSU_BASE_ADDR		0x303E0000

#define MX8MQ_AIPS2_BASE_ADDR		0x305F0000
#define MX8MQ_PWM1_BASE_ADDR		0x30660000
#define MX8MQ_PWM2_BASE_ADDR		0x30670000
#define MX8MQ_PWM3_BASE_ADDR		0x30680000
#define MX8MQ_PWM4_BASE_ADDR		0x30690000
#define MX8MQ_SYSCNT_RD_BASE_ADDR	0x306A0000
#define MX8MQ_SYSCNT_CMP_BASE_ADDR	0x306B0000
#define MX8MQ_SYSCNT_CTRL_BASE_ADDR	0x306C0000
#define MX8MQ_GPT6_BASE_ADDR		0x306E0000
#define MX8MQ_GPT5_BASE_ADDR		0x306F0000
#define MX8MQ_GPT4_BASE_ADDR		0x30700000
#define MX8MQ_PERFMON1_BASE_ADDR	0x307C0000
#define MX8MQ_PERFMON2_BASE_ADDR	0x307D0000
#define MX8MQ_QOSC_BASE_ADDR		0x307F0000

#define MX8MQ_SPDIF1_BASE_ADDR		0x30810000
#define MX8MQ_ECSPI1_BASE_ADDR		0x30820000
#define MX8MQ_ECSPI2_BASE_ADDR		0x30830000
#define MX8MQ_ECSPI3_BASE_ADDR		0x30840000
#define MX8MQ_SPDIF2_BASE_ADDR		0x308A0000
#define MX8MQ_SAI2_BASE_ADDR		0x308B0000
#define MX8MQ_SAI3_BASE_ADDR		0x308C0000
#define MX8MQ_SPBA1_BASE_ADDR		0x308F0000
#define MX8MQ_CAAM_BASE_ADDR		0x30900000
#define MX8MQ_AIPS3_BASE_ADDR		0x309F0000
#define MX8MQ_MIPI_PHY_BASE_ADDR	0x30A00000
#define MX8MQ_MIPI_DSI_BASE_ADDR	0x30A10000
#define MX8MQ_I2C1_BASE_ADDR		0x30A20000
#define MX8MQ_I2C2_BASE_ADDR		0x30A30000
#define MX8MQ_I2C3_BASE_ADDR		0x30A40000
#define MX8MQ_I2C4_BASE_ADDR		0x30A50000
#define MX8MQ_MIPI_CSI_BASE_ADDR	0x30A70000
#define MX8MQ_MIPI_CSI_PHY1_BASE_ADDR	0x30A80000
#define MX8MQ_CSI1_BASE_ADDR		0x30A90000
#define MX8MQ_MU_A_BASE_ADDR		0x30AA0000
#define MX8MQ_MU_B_BASE_ADDR		0x30AB0000
#define MX8MQ_SEMAPHOR_HS_BASE_ADDR	0x30AC0000
#define MX8MQ_USDHC1_BASE_ADDR		0x30B40000
#define MX8MQ_USDHC2_BASE_ADDR		0x30B50000
#define MX8MQ_MIPI_CS2_BASE_ADDR	0x30B60000
#define MX8MQ_MIPI_CSI_PHY2_BASE_ADDR	0x30B70000
#define MX8MQ_CSI2_BASE_ADDR		0x30B80000
#define MX8MQ_QSPI0_BASE_ADDR		0x30BB0000
#define MX8MQ_QSPI0_AMBA_BASE		0x08000000
#define MX8MQ_SDMA1_BASE_ADDR		0x30BD0000
#define MX8MQ_ENET1_BASE_ADDR		0x30BE0000

#define MX8MQ_HDMI_CTRL_BASE_ADDR	0x32C00000
#define MX8MQ_AIPS4_BASE_ADDR		0x32DF0000
#define MX8MQ_DC1_BASE_ADDR		0x32E00000
#define MX8MQ_DC2_BASE_ADDR		0x32E10000
#define MX8MQ_DC3_BASE_ADDR		0x32E20000
#define MX8MQ_HDMI_SEC_BASE_ADDR	0x32E40000
#define MX8MQ_TZASC_BASE_ADDR		0x32F80000
#define MX8MQ_MTR_BASE_ADDR		0x32FB0000
#define MX8MQ_PLATFORM_CTRL_BASE_ADDR	0x32FE0000

#define MX8MQ_MXS_APBH_BASE		0x33000000
#define MX8MQ_MXS_GPMI_BASE		0x33002000
#define MX8MQ_MXS_BCH_BASE		0x33004000

#define MX8MQ_USB1_BASE_ADDR		0x38100000
#define MX8MQ_USB2_BASE_ADDR		0x38200000
#define MX8MQ_USB1_PHY_BASE_ADDR	0x381F0000
#define MX8MQ_USB2_PHY_BASE_ADDR	0x382F0000

#define MX8MQ_MXS_LCDIF_BASE		LCDIF_BASE_ADDR

#define MX8MQ_SRC_IPS_BASE_ADDR		0x30390000
#define MX8MQ_SRC_DDRC_RCR_ADDR		0x30391000
#define MX8MQ_SRC_DDRC2_RCR_ADDR	0x30391004

#define MX8MQ_DDRC_PHY_BASE_ADDR	0x3c000000
#define MX8MQ_DDRC_DDR_SS_GPR0		(MX8MQ_DDRC_PHY_BASE_ADDR + 0x01000000)
#define MX8MQ_DDRC_IPS_BASE_ADDR(X)	(0x3d400000 + ((X) * 0x2000000))
#define MX8MQ_DDRC_CTL_BASE_ADDR	MX8MQ_DDRC_IPS_BASE_ADDR(0)
#define MX8MQ_DDR_CSD1_BASE_ADDR	0x40000000

#endif /* __MACH_IMX8MQ_REGS_H */
