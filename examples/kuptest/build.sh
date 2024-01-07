#!/bin/bash -ex

#
#	Copyright (c) 2024 Scott Duensing, scott@kangaroopunch.com
#
#	Permission is hereby granted, free of charge, to any person obtaining a copy
#	of this software and associated documentation files (the "Software"), to deal
#	in the Software without restriction, including without limitation the rights
#	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#	copies of the Software, and to permit persons to whom the Software is
#	furnished to do so, subject to the following conditions:
#
#	The above copyright notice and this permission notice shall be included in
#	all copies or substantial portions of the Software.
#
#	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#	SOFTWARE.
#


F256=$(pwd)/../..
LLVM=${F256}/llvm-mos
SETTINGS=${LLVM}/mos-platform/f256k/lib/settings.ld
PATH=${LLVM}/bin:${PATH}

START=0x2100

echo "__f256_start = ${START};" > ${SETTINGS}
mos-f256k-clang -o kuptest -Os kuptest.c
mv -f kuptest kuptest.bin

${F256}/header/header \
	kup \
	kuptest.bin kuptest.kup \
	1 ${START} \
	"kuptest" \
	" " \
	"Testing KUP Applications"

#llvm-nm kuptest.elf
llvm-objdump -d --print-imm-hex kuptest.elf
hexdump -C kuptest.bin
