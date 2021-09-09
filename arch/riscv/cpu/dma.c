/* SPDX-License-Identifier: GPL-2.0 */

#include <common.h>
#include <xfuncs.h>
#include <asm/dma.h>
#include <malloc.h>

static void __dma_flush_range(dma_addr_t start, dma_addr_t end)
{
}

static void *__dma_alloc_coherent(size_t size, dma_addr_t *dma_handle)
{
	void *ret;

	ret = xmemalign(PAGE_SIZE, size);

	memset(ret, 0, size);

	if (dma_handle)
		*dma_handle = (dma_addr_t)ret;

	return ret;
}

static void __dma_free_coherent(void *vaddr, dma_addr_t dma_handle, size_t size)
{
	free(vaddr);
}

static const struct dma_ops coherent_dma_ops = {
	.alloc_coherent = __dma_alloc_coherent,
	.free_coherent = __dma_free_coherent,
	.flush_range = __dma_flush_range,
	.inv_range = __dma_flush_range,
};

static const struct dma_ops *dma_ops = &coherent_dma_ops;

void *dma_alloc_coherent(size_t size, dma_addr_t *dma_handle)
{
	return dma_ops->alloc_coherent(size, dma_handle);
}

void dma_free_coherent(void *vaddr, dma_addr_t dma_handle, size_t size)
{
	dma_ops->free_coherent(vaddr, dma_handle, size);
}

void dma_set_ops(const struct dma_ops *ops)
{
	dma_ops = ops;
}

void dma_sync_single_for_cpu(dma_addr_t address, size_t size, enum dma_data_direction dir)
{
        /*
         * FIXME: This function needs a device argument to support non 1:1 mappings
         */
        if (dir != DMA_TO_DEVICE)
                dma_ops->inv_range(address, address + size);
}

void dma_sync_single_for_device(dma_addr_t address, size_t size, enum dma_data_direction dir)
{
        /*
         * FIXME: This function needs a device argument to support non 1:1 mappings
         */

        if (dir == DMA_FROM_DEVICE)
                dma_ops->inv_range(address, address + size);
        else
                dma_ops->flush_range(address, address + size);
}
