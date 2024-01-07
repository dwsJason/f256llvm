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


#ifndef F256_H
#define F256_H


#ifdef __cplusplus
extern "C"
{
#endif


#include <stdlib.h>
#include "stddclmr.h"

#include "api.h"

#include "f256_dma.h"
#include "f256_intmath.h"
#include "f256_irq.h"
#include "f256jr.h"
#include "f256_rtc.h"
#include "f256_sprites.h"
#include "f256_tiles.h"
#include "f256_timers.h"
#include "f256_via.h"
#include "f256_xymath.h"


typedef unsigned char byte;


// Single-byte
#define PEEK(addy)         ((byte)*(volatile byte *)(addy))
#define POKE(addy, value)  (*(volatile byte *)(addy) = (value))

// Word (two bytes)
#define PEEKW(addy)        ((uint16_t)*(volatile uint16_t *)(addy))
#define POKEW(addy, value) (*(volatile uint16_t *)(addy) = (value))

// Address (three bytes)
//#define PEEKA
#define POKEA(addy, value) 	POKE(addy, value & 0xFF); POKE(addy + 1, (value >> 8) & 0xFF); POKE(addy + 2, (value >> 16) & 0xFF)

// Double-word (four bytes)
#define PEEKD(addy)        ((uint_32)*(volatile uint32_t *)(addy))
#define POKED(addy,value)  (*(volatile uint32_t *)(addy) = (value))

#define VECTOR(member)     (size_t)(&((struct call *)0xff00)->member)
#define EVENT(member)      (size_t)(&((struct events *)0)->member)
#define CALL(fn) \
asm("jsr %[addy] \n" \
	"stz %[err] \n" \
	"ror %[err]" \
	: [err] "+m"(error) \
	: [addy] "i"(VECTOR(fn)) \
	: "a", "x", "y", "c", "v");


extern struct event_t event;  // The event struct is allocated in crt0.
extern char           error;


void     f256Init(void);
uint16_t rndRead(void);
void     rndSeed(uint16_t seed);


#include "text.h"
#include "bitmap.h"
#include "dma.h"


#ifdef __cplusplus
}
#endif


#endif // F256_H
