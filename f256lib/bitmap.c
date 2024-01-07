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


#include "bitmap.h"
#include "dma.h"


static uint16_t _MAX_X;
static uint16_t _MAX_Y;
static uint32_t _PAGE_SIZE;
static uint32_t _BITMAP_BASE[3];   // Maximum of 3 pages possible.
static byte     _color;
static byte     _page;


char error;


void bitmapClear(void) {
	dmaFill(_BITMAP_BASE[_page], _PAGE_SIZE, _color);
}


void bitmapDefineColor(byte slot, byte r, byte g, byte b) {
	byte  mmu = PEEK(MMU_IO_CTRL);  // Get current MMU state.
	byte *write;

	POKE(MMU_IO_CTRL, MMU_IO_PAGE_1);  // Swap I/O page 1 into bank 6.

	write = (byte *)VKY_GR_CLUT_0 + slot * 4;
	*write++ = b;
	*write++ = g;
	*write++ = r;
	*write++ = 0xff;

	POKE(MMU_IO_CTRL, mmu);  // Restore MMU state.
}


void bitmapGetResolution(uint16_t *x, uint16_t *y) {
	*x = _MAX_X;
	*y = _MAX_Y;
}


void bitmapLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
	uint16_t x;
	uint16_t y;
	int16_t  dx;
	int16_t  dy;
	int16_t  incX;
	int16_t  incY;
	int16_t  balance;

	if (x2 >= x1) {
		dx = x2 - x1;
		incX = 1;
	} else {
		dx = x1 - x2;
		incX = -1;
	}

	if (y2 >= y1) {
		dy = y2 - y1;
		incY = 1;
	} else {
		dy = y1 - y2;
		incY = -1;
	}

	x = x1;
	y = y1;

	if (dx >= dy) {
		dy <<= 1;
		balance = dy - dx;
		dx <<= 1;
		while (x != x2) {
			bitmapPutPixel(x, y);
			if (balance >= 0) {
				y += incY;
				balance -= dx;
			}
			balance += dy;
			x += incX;
		}
		bitmapPutPixel(x, y);
	} else {
		dx <<= 1;
		balance = dx - dy;
		dy <<= 1;
		while (y != y2) {
			bitmapPutPixel(x, y);
			if (balance >= 0) {
				x += incX;
				balance -= dy;
			}
			balance += dx;
			y += incY;
		}
		bitmapPutPixel(x, y);
	}
}


void bitmapPutPixel(uint16_t x, uint16_t y) {
	uint32_t  pixelRAM;
	byte      block;

	// We only map 8k of the bitmap into CPU RAM at once.
	// We use slot 5 for this.  We need to figure out
	// where our pixel lands and bring that into RAM.
	pixelRAM = _BITMAP_BASE[_page] + ((int32_t)y * (int32_t)_MAX_X) + (int32_t)x;
	block = pixelRAM / 0x2000;
	pixelRAM &= 0x1FFF;  // Find offset into this block.
	POKE(MMU_MEM_BANK_5, block);
	POKE(0xa000 + pixelRAM, _color);
//	POKE(MMU_MEM_BANK_5, 5);
}


void bitmapReset(void) {
	byte     mmu = PEEK(MMU_IO_CTRL);  // Get current MMU state.
	int      x;
	uint32_t realSize;
	uint32_t pageBlocks;
	uint32_t eightK = 0x2000;

	_MAX_X       = 320;
	_MAX_Y       = 240;
	_PAGE_SIZE   = (uint32_t)_MAX_X * (uint32_t)_MAX_Y;

	// I could hardcode this, but this preserves the math so I don't forget later.
	pageBlocks   = _PAGE_SIZE / eightK;
	if ((pageBlocks * eightK) != _PAGE_SIZE) {
		// Fractional pageBlock.  Round up.
		pageBlocks++;
	}
	realSize = pageBlocks * eightK;

	_BITMAP_BASE[0] = 0x10000;
	_BITMAP_BASE[1] = _BITMAP_BASE[0] + realSize;  // Page 2 = 0x24000
	_BITMAP_BASE[2] = _BITMAP_BASE[1] + realSize;  // Page 3 = 0x38000

	print("\nbase0 = ");  printInt(_BITMAP_BASE[0]);
	print("\nbase1 = ");  printInt(_BITMAP_BASE[1]);
	print("\nbase2 = ");  printInt(_BITMAP_BASE[2]);

	// Set palette to a gradient so there's at least *something*.
	for (x=0; x<256; x++) bitmapDefineColor(x, x, x, x);

	POKE(MMU_IO_CTRL, MMU_IO_PAGE_0);  // Swap I/O page 0 into bank 6.

	POKE(VKY_LAYER_CTRL_0, 16);  // Bitmaps on all layers.
	POKE(VKY_LAYER_CTRL_1, 1);   // Bitmaps on all layers.

	// Turn everthing on for setup.
	POKE(VKY_BM0_CTRL, 1);
	POKE(VKY_BM1_CTRL, 0);
	POKE(VKY_BM2_CTRL, 0);

	// Set up bitmap memory.
	POKEA(VKY_BM0_ADDR_L, _BITMAP_BASE[0]);  // Location of bitmap data.
	POKEA(VKY_BM1_ADDR_L, _BITMAP_BASE[1]);  // Location of bitmap data.
	POKEA(VKY_BM2_ADDR_L, _BITMAP_BASE[2]);  // Location of bitmap data.

	// Enable the first bitmap.
	bitmapShowPage(0);

	POKE(MMU_IO_CTRL, mmu);  // Restore MMU state.

	// Clear all pages.
	_color = 0;
	//for (_page=0; _page<3; _page++) bitmapClear();
	_page  = 0;
	bitmapClear();
	_color = 255;
}


void bitmapSetColor(byte c) {
	_color = c;
}


void bitmapSetPage(byte p) {
	_page = p;
}


void bitmapShowPage(byte p) {
	POKE(VKY_BM0_CTRL, p == 0 ? 1 : 0);  // Enable bitmap 0, GLUT 0.
	POKE(VKY_BM1_CTRL, p == 1 ? 1 : 0);
	POKE(VKY_BM2_CTRL, p == 2 ? 1 : 0);
}
