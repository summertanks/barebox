/* SPDX-License-Identifier: GPL-2.0-only */
/* SPDX-FileCopyrightText: 2021 Yann Sionneau <ysionneau@kalray.eu>, Kalray Inc. */

#ifndef __ASM_DMA_H
#define __ASM_DMA_H

#include <common.h>

#define KVX_DDR_32BIT_RAM_WINDOW_BA	(0x80000000ULL)
#define KVX_DDR_64BIT_RAM_WINDOW_BA	(0x100000000ULL)
#define MAX_32BIT_ADDR			(0xffffffffULL)

#define dma_alloc dma_alloc
static inline void *dma_alloc(size_t size)
{
	return xmemalign(64, ALIGN(size, 64));
}

static inline void *dma_alloc_coherent(size_t size, dma_addr_t *dma_handle)
{
	BUILD_BUG_ON_MSG(1, "dma_alloc_coherent not supported: "
			"MMU support is required to map uncached pages");
	return NULL;
}

static inline void dma_free_coherent(void *mem, dma_addr_t dma_handle,
				     size_t size)
{
	free(mem);
}

#endif /* __ASM_DMA_H */
