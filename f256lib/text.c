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


#include "text.h"


char error;


colorT textColors[16] = {
	{ 0x00, 0x00, 0x00 },  // 0 Black
	{ 0xdd, 0x00, 0x33 },  // 1 Deep Red
	{ 0x00, 0x00, 0x99 },  // 2 Dark Blue
	{ 0xdd, 0x22, 0xdd },  // 3 Purple
	{ 0x00, 0x77, 0x22 },  // 4 Dark Green
	{ 0x55, 0x55, 0x55 },  // 5 Dark Gray
	{ 0x22, 0x22, 0xff },  // 6 Medium Blue
	{ 0x66, 0xaa, 0xff },  // 7 Light Blue
	{ 0x88, 0x55, 0x00 },  // 8 Brown
	{ 0xff, 0x66, 0x00 },  // 9 Orange
	{ 0xaa, 0xaa, 0xaa },  // A Light Gray
	{ 0xff, 0x99, 0x88 },  // B Pink
	{ 0x00, 0xdd, 0x00 },  // C Light Green
	{ 0xff, 0xff, 0x00 },  // D Yellow
	{ 0x55, 0xff, 0x99 },  // E Aquamarine
	{ 0xff, 0xff, 0xff }   // F White
};


static byte  _MAX_COL = 80;
static byte  _MAX_ROW = 30;
static byte  _row     = 0;
static byte  _col     = 0;
static byte  _fcolor  = 15;
static byte  _bcolor  = 0;
static byte  _ccolor  = 240;


// Clear screen to current text attributes.
void cls(void) {
	int   i;
	byte  mmu  = PEEK(MMU_IO_CTRL);  // Get current MMU state.
	volatile byte *vram = (byte *)TEXT_MATRIX;

	POKE(MMU_IO_CTRL, MMU_IO_TEXT);     // Swap I/O page 2 into bank 6.
	for (i = 0; i < _MAX_COL * _MAX_ROW; i++) *vram++ = 32;

	POKE(MMU_IO_CTRL, MMU_IO_COLOR);  // Swap I/O page 3 into bank 6.
	vram = (byte *)TEXT_MATRIX;
	for (i = 0; i < _MAX_COL * _MAX_ROW; i++) *vram++ = _ccolor;

	POKE(MMU_IO_CTRL, mmu);  // Restore MMU state.

	gotoxy(0, 0);
}


// Define text color.
void defineTextColor(byte slot, byte fr, byte fg, byte fb, byte br, byte bg, byte bb) {
	byte  mmu = PEEK(MMU_IO_CTRL);  // Get current MMU state.
	byte *write;

	POKE(MMU_IO_CTRL, MMU_IO_PAGE_0);  // Swap I/O page 0 into bank 6.

	write = (byte *)VKY_TXT_FGLUT + slot * 4;
	*write++ = fb;
	*write++ = fg;
	*write++ = fr;
	*write++ = 0xff;

	write = (byte *)VKY_TXT_BGLUT + slot * 4;
	*write++ = bb;
	*write++ = bg;
	*write++ = br;
	*write++ = 0xff;

	POKE(MMU_IO_CTRL, mmu);  // Restore MMU state.
}


// Move cursor.
void gotoxy(byte x, byte y) {
	byte mmu;

	mmu = PEEK(MMU_IO_CTRL);  // Get current MMU state.
	POKE(MMU_IO_CTRL, MMU_IO_PAGE_0);  // Swap I/O page 0 into bank 6.

	_col = x;
	POKE(VKY_CRSR_X_L, _col);  // Set cursor X position.
	POKE(VKY_CRSR_X_H, 0);

	_row = y;
	POKE(VKY_CRSR_Y_L, _row);  // Set cursor Y position.
	POKE(VKY_CRSR_Y_H, 0);

	POKE(MMU_IO_CTRL, mmu);  // Restore MMU state.
}


// Print a string to the screen.
void print(char *message) {
	int   x      = 0;
	int   i      = 0;
	int   j      = 0;
	byte  mmu    = PEEK(MMU_IO_CTRL);  // Get current MMU state.
	volatile byte *vram = (byte *)TEXT_MATRIX + (_MAX_COL * _row);
	volatile byte *save = 0;

	while (message[x] != 0) {
		switch (message[x]) {
			default:
				POKE(MMU_IO_CTRL, MMU_IO_COLOR);  // Swap I/O page 3 into bank 6.
				vram[_col] = _ccolor;
				POKE(MMU_IO_CTRL, MMU_IO_TEXT);  // Swap I/O page 2 into bank 6.
				vram[_col] = message[x];
				_col++;
				if (_col != _MAX_COL) break;
				// Fall through.
			case 10:
			case 13:
				_col = 0;
				_row++;
				if (_row == _MAX_ROW) {
					// Scroll contents up one line.
					vram = (byte *)TEXT_MATRIX;
					POKE(MMU_IO_CTRL, MMU_IO_COLOR);  // Swap I/O page 3 into bank 6.
					for (j=0; j<2; j++) {
						for (i = 0; i < _MAX_COL * (_MAX_ROW - 1); i++) vram[i] = vram[i+_MAX_COL];
						POKE(MMU_IO_CTRL, MMU_IO_TEXT);  // Swap I/O page 2 into bank 6.
					}
					// Clear bottom line.
					vram += i;
					save = vram;
					POKE(MMU_IO_CTRL, MMU_IO_COLOR);  // Swap I/O page 3 into bank 6.
					for (i = 0; i < _MAX_COL; i++) *vram++ = _ccolor;
					POKE(MMU_IO_CTRL, MMU_IO_TEXT);  // Swap I/O page 2 into bank 6.
					vram = save;
					for (i = 0; i < _MAX_COL; i++) *vram++ = 32;
					// Set up on bottom line.
					_row--;
					vram = (byte *)TEXT_MATRIX + (_MAX_ROW - 1);
				} else {
					vram += _MAX_COL;
				}
				break;
		}
		x++;
	}

	POKE(MMU_IO_CTRL, mmu);  // Restore MMU state.

	gotoxy(_col, _row);
}


void printInt(int32_t value){
	char c[2];

	if (value < 0) {
		print("-");
		value = -value;
	}

	if (value > 9) printInt(value / 10);

	c[0] = '0' + (value % 10);
	c[1] = 0;
	print(c);
}


// Reset display to text, "standard" colors.
void resetText(void) {
	byte  mmu = PEEK(MMU_IO_CTRL);  // Get current MMU state.
	byte  x;
	byte  y;

	_MAX_COL = 80;
	_MAX_ROW = 30;

	_fcolor  = 15;
	_bcolor  = 0;
	_ccolor  = 240;

	POKE(MMU_IO_CTRL, MMU_IO_PAGE_0);  // Swap I/O page 0 into bank 6.

	POKE(VKY_CRSR_CTRL, 3);    // Enable cursor, 1/2s flash.
	POKE(VKY_CRSR_CHAR, '_');  // Set cursor shape.  (199 = Checkerboard)

	// Set up default text colors.
	for (x=0; x<TEXTCOLORS_COUNT; x++)
		defineTextColor(x,
						textColors[x].r,
						textColors[x].g,
						textColors[x].b,
						textColors[x].r,
						textColors[x].g,
						textColors[x].b);

	POKE(MMU_IO_CTRL, mmu);  // Restore MMU state.

	cls();
}


void setTextColor(byte f, byte b) {
	_fcolor = f;
	_bcolor = b;
	_ccolor = (f << 4) + b;
}
