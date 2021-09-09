#include <common.h>
#include <linux/sizes.h>
#include <generated/mach-types.h>
#include <asm/barebox-arm-head.h>
#include <asm/barebox-arm.h>
#include <mach/imx23-regs.h>

ENTRY_FUNCTION(start_imx23_evk, r0, r1, r2)
{
	arm_cpu_lowlevel_init();
	barebox_arm_entry(IMX_MEMORY_BASE, SZ_32M, (void *)MACH_TYPE_MX23EVK);
}
