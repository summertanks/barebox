/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Alex Zuepke <azu@sysgo.de>
 */

#ifndef _BAREBOX_ARM_H_
#define _BAREBOX_ARM_H_

#include <linux/sizes.h>
#include <asm-generic/memory_layout.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/compiler.h>
#include <asm/barebox-arm-head.h>
#include <asm/sections.h>

/*
 * We have a 4GiB address space split into 1MiB sections, with each
 * section header taking 4 bytes
 */
#define ARM_TTB_SIZE	(SZ_4G / SZ_1M * sizeof(u32))

unsigned long get_runtime_offset(void);

/* global_variable_offset() - Access global variables when not running at link address
 *
 * Get the offset of global variables when not running at the address we are
 * linked at.
 */
static inline unsigned long global_variable_offset(void)
{
#ifdef CONFIG_CPU_V8
	unsigned long text;

	__asm__ __volatile__(
		"adr    %0, _text\n"
		: "=r" (text)
		:
		: "memory");
	return text - (unsigned long)_text;
#else
	return get_runtime_offset();
#endif
}

void setup_c(void);
void pbl_barebox_break(void);
void relocate_to_current_adr(void);
void relocate_to_adr(unsigned long target);
void relocate_to_adr_full(unsigned long target);
void __noreturn barebox_arm_entry(unsigned long membase, unsigned long memsize, void *boarddata);

struct barebox_arm_boarddata {
#define BAREBOX_ARM_BOARDDATA_MAGIC	0xabe742c3
	u32 magic;
	u32 machine; /* machine number to pass to barebox. This may or may
		      * not be a ARM machine number registered on arm.linux.org.uk.
		      * It must only be unique across barebox. Please use a number
		      * that do not potientially clashes with registered machines,
		      * i.e. use a number > 0x10000.
		      */
};

/*
 * Create a boarddata struct at given address. Suitable to be passed
 * as boarddata to barebox_arm_entry(). The machine can be retrieved
 * later with barebox_arm_machine().
 */
static inline void boarddata_create(void *adr, u32 machine)
{
	struct barebox_arm_boarddata *bd = adr;

	bd->magic = BAREBOX_ARM_BOARDDATA_MAGIC;
	bd->machine = machine;
}

u32 barebox_arm_machine(void);

unsigned long arm_mem_ramoops_get(void);
unsigned long arm_mem_endmem_get(void);

struct barebox_arm_boarddata *barebox_arm_get_boarddata(void);

#if defined(CONFIG_RELOCATABLE) && defined(CONFIG_ARM_EXCEPTIONS)
void arm_fixup_vectors(void);
#else
static inline void arm_fixup_vectors(void)
{
}
#endif

void *barebox_arm_boot_dtb(void);

static inline unsigned long arm_mem_stack_top(unsigned long membase,
					      unsigned long endmem)
{
	if (IS_ENABLED(CONFIG_BOOTM_OPTEE) || IS_ENABLED(CONFIG_PBL_OPTEE))
		endmem -= OPTEE_SIZE;

	return endmem - SZ_64K;
}

static inline unsigned long arm_mem_stack(unsigned long membase,
					  unsigned long endmem)
{
	return arm_mem_stack_top(membase, endmem) - STACK_SIZE;
}

static inline unsigned long arm_mem_ttb(unsigned long membase,
					unsigned long endmem)
{
	endmem = arm_mem_stack(membase, endmem);
	endmem = ALIGN_DOWN(endmem, ARM_TTB_SIZE) - ARM_TTB_SIZE;

	return endmem;
}

static inline unsigned long arm_mem_early_malloc(unsigned long membase,
						 unsigned long endmem)
{
	return arm_mem_ttb(membase, endmem) - SZ_128K;
}

static inline unsigned long arm_mem_early_malloc_end(unsigned long membase,
						     unsigned long endmem)
{
	return arm_mem_ttb(membase, endmem);
}

static inline unsigned long arm_mem_ramoops(unsigned long membase,
					    unsigned long endmem)
{
	endmem = arm_mem_ttb(membase, endmem);
#ifdef CONFIG_FS_PSTORE_RAMOOPS
	endmem -= CONFIG_FS_PSTORE_RAMOOPS_SIZE;
	endmem = ALIGN_DOWN(endmem, SZ_4K);
#endif

	return endmem;
}

static inline unsigned long arm_mem_barebox_image(unsigned long membase,
						  unsigned long endmem,
						  unsigned long size)
{
	endmem = arm_mem_ramoops(membase, endmem);

	if (IS_ENABLED(CONFIG_RELOCATABLE)) {
		return ALIGN_DOWN(endmem - size, SZ_1M);
	} else {
		if (TEXT_BASE >= membase && TEXT_BASE < endmem)
			return TEXT_BASE;
		else
			return endmem;
	}
}

#define ENTRY_FUNCTION(name, arg0, arg1, arg2)				\
	void name (uint32_t r0, uint32_t r1, uint32_t r2);		\
									\
	static void __##name(uint32_t, uint32_t, uint32_t);		\
									\
	void NAKED __section(.text_head_entry_##name)	name		\
				(uint32_t r0, uint32_t r1, uint32_t r2)	\
		{							\
			__barebox_arm_head();				\
			__##name(r0, r1, r2);				\
		}							\
		static void NAKED noinline __##name			\
			(uint32_t arg0, uint32_t arg1, uint32_t arg2)

/*
 * When using compressed images in conjunction with relocatable images
 * the PBL code must pick a suitable place where to uncompress the barebox
 * image. For doing this the PBL code must know the size of the final
 * image including the BSS segment. The BSS size is unknown to the PBL
 * code, so define a maximum BSS size here.
 */
#define MAX_BSS_SIZE SZ_1M

#define barebox_image_size (__image_end - __image_start)

#ifdef CONFIG_CPU_32
#define NAKED __naked
#else
/*
 * There is no naked support for aarch64, so do not rely on it.
 * This basically means we must have a stack configured when a
 * function with the naked attribute is entered. On nowadays hardware
 * the ROM should have some basic stack already. If not, set one
 * up before jumping into the barebox entry functions.
 */
#define NAKED
#endif

#endif	/* _BAREBOX_ARM_H_ */
