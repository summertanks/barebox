// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2020 Lucas Stach <dev@lynxeye.de>
 */

#include <asm/barebox-arm.h>
#include <common.h>
#include <debug_ll.h>
#include <firmware.h>
#include <i2c/i2c-early.h>
#include <mach/atf.h>
#include <mach/esdctl.h>
#include <mach/generic.h>
#include <mach/imx-gpio.h>
#include <mach/imx8m-ccm-regs.h>
#include <mach/imx8mq-regs.h>
#include <mach/iomux-mx8mq.h>
#include <mach/xload.h>
#include <soc/imx8m/ddr.h>

extern char __dtb_imx8mq_mnt_reform2_start[];

#define UART_PAD_CTRL	MUX_PAD_CTRL(MX8MQ_PAD_CTL_DSE_65R)

static void mnt_reform_setup_uart(void)
{
	void __iomem *uart = IOMEM(MX8M_UART1_BASE_ADDR);

	imx8m_early_setup_uart_clock();

	imx8mq_setup_pad(IMX8MQ_PAD_UART1_TXD__UART1_TX | UART_PAD_CTRL);
	imx8m_uart_setup(uart);

	pbl_set_putc(imx_uart_putc, uart);

	putc_ll('>');
}

static void i2c_mux_set(void *i2c, u8 channel)
{
	int ret;
	u8 buf[1];
	struct i2c_msg msgs[] = {
		{
			.addr = 0x70,
			.buf = buf,
			.len = 1,
		},
	};

	buf[0] = 1 << channel;

	ret = i2c_fsl_xfer(i2c, msgs, ARRAY_SIZE(msgs));
	if (ret != 1)
		pr_err("failed to set i2c mux\n");
}

static void i2c_regulator_set_voltage(void *i2c, u8 reg, u8 voffs)
{
	int ret;
	u8 buf[2];
	struct i2c_msg msgs[] = {
		{
			.addr = 0x60,
			.buf = buf,
			.len = 2,
		},
	};

	buf[0] = reg;
	buf[1] = 0x80 + voffs;

	ret = i2c_fsl_xfer(i2c, msgs, ARRAY_SIZE(msgs));
	if (ret != 1)
		pr_err("failed to set voltage\n");
}

#define I2C_PAD_CTRL	MUX_PAD_CTRL(MX8MQ_PAD_CTL_DSE_45R | \
				     MX8MQ_PAD_CTL_HYS | \
				     MX8MQ_PAD_CTL_PUE)

static void mnt_reform_init_power(void)
{
	void *i2c;

	imx8mq_setup_pad(IMX8MQ_PAD_I2C1_SCL__I2C1_SCL | I2C_PAD_CTRL);
	imx8mq_setup_pad(IMX8MQ_PAD_I2C1_SDA__I2C1_SDA | I2C_PAD_CTRL);
	imx8m_ccgr_clock_enable(IMX8M_CCM_CCGR_I2C1);

	i2c = imx8m_i2c_early_init(IOMEM(MX8MQ_I2C1_BASE_ADDR));

	/* de-assert i2c mux reset */
	imx8m_gpio_direction_output(IOMEM(MX8MQ_GPIO1_BASE_ADDR), 4, 1);
	/* ARM/DRAM_CORE VSEL */
	imx8m_gpio_direction_output(IOMEM(MX8MQ_GPIO3_BASE_ADDR), 24, 0);
	/* DRAM VSEL */
	imx8m_gpio_direction_output(IOMEM(MX8MQ_GPIO2_BASE_ADDR), 11, 0);
	/* SOC/GPU/VPU VSEL */
	imx8m_gpio_direction_output(IOMEM(MX8MQ_GPIO2_BASE_ADDR), 20, 0);

	/* enable I2C1A, ARM/DRAM */
	i2c_mux_set(i2c, 0);
	/* .6 + .40 = 1.00V */
	i2c_regulator_set_voltage(i2c, 0, 40);
	i2c_regulator_set_voltage(i2c, 1, 40);

	/* enable I2C1B, DRAM 1.1V */
	i2c_mux_set(i2c, 1);
	/* .6 + .50 = 1.10V */
	i2c_regulator_set_voltage(i2c, 0, 50);
	i2c_regulator_set_voltage(i2c, 1, 50);

	/* enable I2C1C, SOC/GPU/VPU */
	i2c_mux_set(i2c, 2);
	/*.6 + .30 = .90V */
	i2c_regulator_set_voltage(i2c, 0, 30);
	i2c_regulator_set_voltage(i2c, 1, 30);

	/* enable I2C1D */
	i2c_mux_set(i2c, 3);
}

extern struct dram_timing_info mnt_reform_dram_timing;

static __noreturn noinline void mnt_reform_start(void)
{
	/*
	 * If we are in EL3 we are running for the first time and need to
	 * initialize the power supplies, DRAM and run TF-A (BL31).
	 * The TF-A will then jump to DRAM in EL2.
	 */
	if (current_el() == 3) {
		size_t bl31_size;
		const u8 *bl31;
		enum bootsource src;
		int instance;

		mnt_reform_setup_uart();

		mnt_reform_init_power();

		imx8mq_ddr_init(&mnt_reform_dram_timing);

		imx8mq_get_boot_source(&src, &instance);
		switch (src) {
		case BOOTSOURCE_MMC:
			imx8m_esdhc_load_image(instance, false);
			break;
		case BOOTSOURCE_SERIAL:
			imx8m_esdhc_load_image(1, false);
			break;
		default:
			printf("Unhandled bootsource BOOTSOURCE_%d\n", src);
			hang();
		}

		/*
		 * On completion the TF-A will jump to MX8M_ATF_BL33_BASE_ADDR
		 * in EL2. Copy the image there, but replace the PBL part of
		 * that image with ourselves. On a high assurance boot only the
		 * currently running code is validated and contains the checksum
		 * for the piggy data, so we need to ensure that we are running
		 * the same code in DRAM.
		 */
		memcpy((void *)MX8M_ATF_BL33_BASE_ADDR,
		       __image_start, barebox_pbl_size);

		get_builtin_firmware(imx8mq_bl31_bin, &bl31, &bl31_size);

		imx8mq_atf_load_bl31(bl31, bl31_size);
	}

	/*
	 * Standard entry we hit once we initialized both DDR and ATF
	 */
	imx8mq_barebox_entry(__dtb_imx8mq_mnt_reform2_start);
}

ENTRY_FUNCTION(start_mnt_reform, r0, r1, r2)
{
	imx8mq_cpu_lowlevel_init();

	relocate_to_current_adr();
	setup_c();

	mnt_reform_start();
}
