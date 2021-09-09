// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2012 Regents of the University of California
 * Copyright (C) 2017 SiFive
 *
 * All RISC-V systems have a timer attached to every hart.  These timers can
 * either be read from the "time" and "timeh" CSRs, and can use the SBI to
 * setup events, or directly accessed using MMIO registers.
 */
#include <common.h>
#include <init.h>
#include <clock.h>
#include <asm/timer.h>
#include <asm/csr.h>
#include <asm/system.h>

static u64 notrace riscv_timer_get_count_sbi(void)
{
	__maybe_unused u32 hi, lo;

	if (IS_ENABLED(CONFIG_64BIT))
		return csr_read(CSR_TIME);

	do {
		hi = csr_read(CSR_TIMEH);
		lo = csr_read(CSR_TIME);
	} while (hi != csr_read(CSR_TIMEH));

	return ((u64)hi << 32) | lo;
}

static u64 notrace riscv_timer_get_count_rdcycle(void)
{
	__maybe_unused u32 hi, lo;

	if (IS_ENABLED(CONFIG_64BIT))
		return csr_read(CSR_CYCLE);

	do {
		hi = csr_read(CSR_CYCLEH);
		lo = csr_read(CSR_CYCLE);
	} while (hi != csr_read(CSR_CYCLEH));

	return ((u64)hi << 32) | lo;
}

static u64 notrace riscv_timer_get_count(void)
{
	if (riscv_mode() == RISCV_S_MODE)
		return riscv_timer_get_count_sbi();
	else
		return riscv_timer_get_count_rdcycle();
}

static struct clocksource riscv_clocksource = {
	.read		= riscv_timer_get_count,
	.mask		= CLOCKSOURCE_MASK(64),
	.priority	= 100,
};

static int riscv_timer_init(struct device_d* dev)
{
	dev_dbg(dev, "running at %lu Hz\n", riscv_timebase);

	riscv_clocksource.mult = clocksource_hz2mult(riscv_timebase, riscv_clocksource.shift);

	return init_clock(&riscv_clocksource);
}

static struct driver_d riscv_timer_driver = {
	.name = "riscv-timer",
	.probe = riscv_timer_init,
};
postcore_platform_driver(riscv_timer_driver);
