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


#include "f256.h"

#include "text.c"
#include "bitmap.c"
#include "dma.c"


void f256Init(void) {
	byte mmu = PEEK(MMU_IO_CTRL);  // Get current MMU state.

	POKE(MMU_IO_CTRL, MMU_IO_PAGE_0);  // Swap I/O page 0 into bank 6.

	//POKE(VKY_MSTR_CTRL_0, 1); // Enable text.
	//POKE(VKY_MSTR_CTRL_0, 12); // Enable bitmaps.
	POKE(VKY_MSTR_CTRL_0, 15); // Enable text and bitmaps.
	//POKE(VKY_MSTR_CTRL_0, 63); // Enable text and all graphics.
	//POKE(VKY_MSTR_CTRL_1, 20); // Enable FON_OVLY and DBL_Y.
	POKE(VKY_MSTR_CTRL_1, 4);  // Enable DBL_Y.

	POKE(MMU_IO_CTRL, mmu);  // Restore MMU state.

	POKE(MMU_MEM_CTRL, 0xb3);  // MLUT editing enabled, editing 3, 3 is active.
	// Set all memory slots to be CPU memory.
	POKE(MMU_MEM_BANK_0, 0);
	POKE(MMU_MEM_BANK_1, 1);
	POKE(MMU_MEM_BANK_2, 2);
	POKE(MMU_MEM_BANK_3, 3);
	POKE(MMU_MEM_BANK_4, 4);
	POKE(MMU_MEM_BANK_5, 5);
	// MMU_MEM_BANK_6 is always mapped to I/O.
	// MMU_MEM_BANK_7 belongs to the MicroKernel.

	rndSeed(0);  //***TODO*** Use clock or something.
}


uint16_t rndRead(void) {
	byte    mmu = PEEK(MMU_IO_CTRL);  // Get current MMU state.
	uint16_t result;

	POKE(MMU_IO_CTRL, MMU_IO_PAGE_0);  // Swap I/O page 0 into bank 6.

	POKE(VKY_RND_CTRL, 1);  // Enable.
	result = PEEKW(VKY_RNDL);

	POKE(MMU_IO_CTRL, mmu);  // Restore MMU state.

	return result;
}


void rndSeed(uint16_t seed) {
	byte mmu = PEEK(MMU_IO_CTRL);  // Get current MMU state.

	POKE(MMU_IO_CTRL, MMU_IO_PAGE_0);  // Swap I/O page 0 into bank 6.

	POKEW(VKY_SEEDL, seed);
	POKE(VKY_RND_CTRL, 3);  // Enable, load seed.

	POKE(MMU_IO_CTRL, mmu);  // Restore MMU state.
}
