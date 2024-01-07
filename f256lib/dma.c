/*
 *	Copyright (c) 2024 Scott Duensing, scott@kangaroopunch.com
 *
 *	Permission is hereby granted, free of charge, to any person obtaining a copy
 *	of this software and associated documentation files (the "Software"), to deal
 *	in the Software without restriction, including without limitation the rights
 *	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *	copies of the Software, and to permit persons to whom the Software is
 *	furnished to do so, subject to the following conditions:
 *
 *	The above copyright notice and this permission notice shall be included in
 *	all copies or substantial portions of the Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *	SOFTWARE.
 */


#include "dma.h"


char error;


static void dmaWait(void);


void dmaFill(uint32_t start, uint32_t length, byte value) {
	byte  mmu = PEEK(MMU_IO_CTRL);  // Get current MMU state.

	POKE(MMU_IO_CTRL, MMU_IO_PAGE_0);  // Swap I/O page 0 into bank 6.

	POKE(DMA_CTRL, DMA_CTRL_FILL | DMA_CTRL_ENABLE);
	POKE(DMA_FILL_VAL, value);
	POKEA(DMA_DST_ADDR, start);
	POKEA(DMA_COUNT, length);
	POKE(DMA_CTRL, DMA_CTRL_FILL | DMA_CTRL_ENABLE | DMA_CTRL_START);

	dmaWait();

	POKE(MMU_IO_CTRL, mmu);  // Restore MMU state.
}


static void dmaWait(void) {
	while (PEEK(DMA_STATUS) & DMA_STAT_BUSY)
		// Spin our wheels.
		;

	POKE(DMA_CTRL, 0);
}
