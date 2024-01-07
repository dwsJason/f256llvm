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


#ifndef TEXT_H
#define TEXT_H


#ifdef __cplusplus
extern "C"
{
#endif


#include "f256.h"


#define TEXT_MATRIX          0xc000  // I/O Page 2


// Apple IIgs Colors, because that's how we roll.
typedef enum textColorsE {
	BLACK = 0,
	DEEP_RED,
	DARK_BLUE,
	PURPLE,
	DARK_GREEN,
	DARK_GRAY,
	MEDIUM_BLUE,
	LIGHT_BLUE,
	BROWN,
	ORANGE,
	LIGHT_GRAY,
	PINK,
	LIGHT_GREEN,
	YELLOW,
	AQUAMARINE,
	WHITE,
	TEXTCOLORS_COUNT
} textColorsT;

typedef struct colorS {
	byte r;
	byte g;
	byte b;
} colorT;

extern colorT textColors[16];


void cls(void);
void defineTextColor(byte slot, byte fr, byte fg, byte fb, byte br, byte bg, byte bb);
void gotoxy(byte x, byte y);
void print(char *message);
void printInt(int32_t value);
void resetText(void);
void setTextColor(byte f, byte b);


#ifdef __cplusplus
}
#endif


#endif // TEXT_H
