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


void bitmap(void);
void text(void);


void bitmap(void) {
	uint16_t  x;
	uint16_t  y;
	uint16_t  x2;
	uint16_t  y2;
	uint16_t  mx;
	uint16_t  my;
	byte      l;
	byte      c = 0;

	bitmapReset();

	bitmapGetResolution(&mx, &my);
	mx--;
	my--;

	for (l=0; l<TEXTCOLORS_COUNT; l++)
		bitmapDefineColor(l,
							textColors[l].r,
							textColors[l].g,
							textColors[l].b);

	l = 0;
	while (1) {
		bitmapSetColor(c++);
		if (c == TEXTCOLORS_COUNT) c = 0;

		x  = rndRead() % mx;
		y  = rndRead() % my;
		x2 = rndRead() % mx;
		y2 = rndRead() % my;

		bitmapLine(x, y, x2, y2);
	}
}


void text(void) {
	resetText();
	print("F256 LIVES!\n");
	setTextColor(LIGHT_GREEN, BLACK);
	print("Green!\n\n");
	setTextColor(ORANGE, BLACK);
	print("byte is ");       printInt(sizeof(byte));
	print("\nint is ");      printInt(sizeof(int));
	print("\nint16_t is ");  printInt(sizeof(int16_t));
	print("\nint32_t is ");  printInt(sizeof(int32_t));
	print("\n");
}


int main(void) {
	f256Init();
	text();
	bitmap();
	return 0;
}
