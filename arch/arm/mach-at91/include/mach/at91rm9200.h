/* SPDX-License-Identifier: GPL-2.0-or-later */
/* SPDX-FileCopyrightText: 2005 Ivan Kokshaysky */
/* SPDX-FileCopyrightText: SAN People */

/*
 * [origin: Linux kernel arch/arm/mach-at91/include/mach/at91rm9200.h]
 *
 * Common definitions.
 * Based on AT91RM9200 datasheet revision E.
 */

#ifndef AT91RM9200_H
#define AT91RM9200_H

/*
 * Peripheral identifiers/interrupts.
 */
#define AT91RM9200_ID_PIOA	2	/* Parallel IO Controller A */
#define AT91RM9200_ID_PIOB	3	/* Parallel IO Controller B */
#define AT91RM9200_ID_PIOC	4	/* Parallel IO Controller C */
#define AT91RM9200_ID_PIOD	5	/* Parallel IO Controller D */
#define AT91RM9200_ID_US0	6	/* USART 0 */
#define AT91RM9200_ID_US1	7	/* USART 1 */
#define AT91RM9200_ID_US2	8	/* USART 2 */
#define AT91RM9200_ID_US3	9	/* USART 3 */
#define AT91RM9200_ID_MCI	10	/* Multimedia Card Interface */
#define AT91RM9200_ID_UDP	11	/* USB Device Port */
#define AT91RM9200_ID_TWI	12	/* Two-Wire Interface */
#define AT91RM9200_ID_SPI	13	/* Serial Peripheral Interface */
#define AT91RM9200_ID_SSC0	14	/* Serial Synchronous Controller 0 */
#define AT91RM9200_ID_SSC1	15	/* Serial Synchronous Controller 1 */
#define AT91RM9200_ID_SSC2	16	/* Serial Synchronous Controller 2 */
#define AT91RM9200_ID_TC0	17	/* Timer Counter 0 */
#define AT91RM9200_ID_TC1	18	/* Timer Counter 1 */
#define AT91RM9200_ID_TC2	19	/* Timer Counter 2 */
#define AT91RM9200_ID_TC3	20	/* Timer Counter 3 */
#define AT91RM9200_ID_TC4	21	/* Timer Counter 4 */
#define AT91RM9200_ID_TC5	22	/* Timer Counter 5 */
#define AT91RM9200_ID_UHP	23	/* USB Host port */
#define AT91RM9200_ID_EMAC	24	/* Ethernet MAC */
#define AT91RM9200_ID_IRQ0	25	/* Advanced Interrupt Controller (IRQ0) */
#define AT91RM9200_ID_IRQ1	26	/* Advanced Interrupt Controller (IRQ1) */
#define AT91RM9200_ID_IRQ2	27	/* Advanced Interrupt Controller (IRQ2) */
#define AT91RM9200_ID_IRQ3	28	/* Advanced Interrupt Controller (IRQ3) */
#define AT91RM9200_ID_IRQ4	29	/* Advanced Interrupt Controller (IRQ4) */
#define AT91RM9200_ID_IRQ5	30	/* Advanced Interrupt Controller (IRQ5) */
#define AT91RM9200_ID_IRQ6	31	/* Advanced Interrupt Controller (IRQ6) */


/*
 * Peripheral physical base addresses.
 */
#define AT91RM9200_BASE_TCB0	0xfffa0000
#define AT91RM9200_BASE_TC0	0xfffa0000
#define AT91RM9200_BASE_TC1	0xfffa0040
#define AT91RM9200_BASE_TC2	0xfffa0080
#define AT91RM9200_BASE_TCB1	0xfffa4000
#define AT91RM9200_BASE_TC3	0xfffa4000
#define AT91RM9200_BASE_TC4	0xfffa4040
#define AT91RM9200_BASE_TC5	0xfffa4080
#define AT91RM9200_BASE_UDP	0xfffb0000
#define AT91RM9200_BASE_MCI	0xfffb4000
#define AT91RM9200_BASE_TWI	0xfffb8000
#define AT91RM9200_BASE_EMAC	0xfffbc000
#define AT91RM9200_BASE_US0	0xfffc0000
#define AT91RM9200_BASE_US1	0xfffc4000
#define AT91RM9200_BASE_US2	0xfffc8000
#define AT91RM9200_BASE_US3	0xfffcc000
#define AT91RM9200_BASE_SSC0	0xfffd0000
#define AT91RM9200_BASE_SSC1	0xfffd4000
#define AT91RM9200_BASE_SSC2	0xfffd8000
#define AT91RM9200_BASE_SPI	0xfffe0000

/*
 * System Peripherals
 */
#define AT91RM9200_BASE_DBGU	AT91_BASE_DBGU0	/* Debug Unit */
#define AT91RM9200_BASE_PIOA	0xfffff400	/* PIO Controller A */
#define AT91RM9200_BASE_PIOB	0xfffff600	/* PIO Controller B */
#define AT91RM9200_BASE_PIOC	0xfffff800	/* PIO Controller C */
#define AT91RM9200_BASE_PIOD	0xfffffa00	/* PIO Controller D */
#define AT91RM9200_BASE_PMC	0xfffffc00
#define AT91RM9200_BASE_ST	0xfffffd00	/* System Timer */
#define AT91RM9200_BASE_RTC	0xfffffe00	/* Real-Time Clock */
#define AT91RM9200_BASE_MC	0xffffff00	/* Memory Controllers */

/*
 * Internal Memory.
 */
#define AT91RM9200_ROM_BASE	0x00100000	/* Internal ROM base address */
#define AT91RM9200_ROM_SIZE	SZ_128K		/* Internal ROM size (128Kb) */

#define AT91RM9200_SRAM_BASE	0x00200000	/* Internal SRAM base address */
#define AT91RM9200_SRAM_SIZE	SZ_16K		/* Internal SRAM size (16Kb) */

#define AT91RM9200_UHP_BASE	0x00300000	/* USB Host controller */

#define AT91_VA_BASE_EMAC	AT91RM9200_BASE_EMAC

#endif
