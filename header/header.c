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


//#include <arpa/inet.h>
#include <winsock.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

#include "stddclmr.h"


/*
 * This program assumes it is being run on a little endian machine.
 */


int utilStricmp(char *a, char *b) {
	for (;; a++, b++) {
		int d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
		if (d != 0 || !*a) {
			return d;
		}
	}
}


int main(int argc, char *argv[]) {
	FILE    *in       = NULL;
	FILE    *out      = NULL;
	int32_t  reserved = 0;
	int32_t  start;
	int32_t  length;
	int32_t  count;
	int      c;
	int8_t   addr;

	if (argc < 2) {
		printf("Usage:  %s [mode] {opts}\n\n", argv[0]);
		printf("  Where [mode] is:  KUP, PGX, or PGZ\n");
		return 1;
	}

	// Add MicroKernel header.
	if (utilStricmp((char *)"kup", argv[1]) == 0) {
		/*
		 * MicroKernel Application
		 *
		 *  Byte  0    signature: $F2
		 *  Byte  1    signature: $56
		 *  Byte  2    the size of program in 8k blocks
		 *  Byte  3    the starting slot of the program (cannot be zero)
		 *  Bytes 4-5  the start address of the program
		 *  Byte  6    header structure version (0 or 1)
		 *  Bytes 7-9  reserved
		 *  Bytes 10-  the zero-terminated name of the program
		 *  Bytes ?-   the zero-terminated arguments for the program (version >= 1)
		 *  Bytes ?-   the zero-terminated description of the program (version >= 1)
		 */
		if (argc != 9) {
			printf("Usage:  %s KUP INPUT.BIN OUTPUT.KUP SLOT START \"NAME\" \"ARG LIST\" \"DESC\"\n", argv[0]);
			return 1;
		}
		in = fopen(argv[2], "rb");
		if (!in) {
			printf("Unable to open input file.\n");
			return 1;
		}
		out = fopen(argv[3], "wb");
		if (!out) {
			fclose(in);
			printf("Unable to open output file.\n");
			return 1;
		}
		// Get binary size in blocks.
		fseek(in, 0, SEEK_END);
		length = ceil((float)ftell(in) / 8192.0);
		fseek(in, 0, SEEK_SET);
		// Write header.
		fputc(0xf2, out);
		fputc(0x56, out);
		fputc((int8_t)length, out);
		fputc((int8_t)atoi(argv[4]), out);
		start = (int16_t)strtol(argv[5], NULL, 0);
		fwrite(&start, sizeof(int16_t), 1, out);
		fputc(0x01, out);  // version
		fwrite(&reserved, sizeof(char), 3, out);
		fputs(argv[6], out);
		fputc(0x00, out);
		if (strlen(argv[7]) > 0) fputs(argv[7], out);
		fputc(0x00, out);
		fputs(argv[8], out);
		fputc(0x00, out);
		// Copy binary into output.
		while ((c = fgetc(in)) != EOF) fputc(c, out);
		fclose(out);
		fclose(in);
	}

	// Add PGX header.
	if (utilStricmp((char *)"pgx", argv[1]) == 0) {
		/*
		 * PGX Program
		 *
		 *  Byte 0-2  signature: PGX
		 *  Byte 3    CPU Type (1=65816, 2=M680x0, 3=6502)
		 *  Byte 4-7  load address - big endian!
		 *  Byte 8-   data
		 */
		if (argc != 5) {
			printf("Usage:  %s PGX INPUT.BIN OUTPUT.PGX START\n", argv[0]);
			return 1;
		}
		in = fopen(argv[2], "rb");
		if (!in) {
			printf("Unable to open input file.\n");
			return 1;
		}
		out = fopen(argv[3], "wb");
		if (!out) {
			fclose(in);
			printf("Unable to open output file.\n");
			return 1;
		}
		// Write header.
		fputc('P', out);
		fputc('G', out);
		fputc('X', out);
		fputc(0x03, out);
		start = htonl((int32_t)strtol(argv[4], NULL, 0));
		fwrite(&start, sizeof(int32_t), 1, out);
		// Copy binary into output.
		while ((c = fgetc(in)) != EOF) fputc(c, out);
		fclose(out);
		fclose(in);
	}

	// Create PGZ package.
	if (utilStricmp((char *)"pgz", argv[1]) == 0) {
		/*
		 * PGZ Program
		 *
		 *  Byte 0    signature ("Z" = 24 bit addresses, "z" = 32 bit)
		 *  Byte 1-3  address of segment #1 (24 bit example)
		 *  Byte 4-6  size of segment #1
		 *  Byte 7-   data
		 *  ...       repeat address/size/data for more segments
		 *  Byte ?    start address
		 *  Byte ?    zeros to indicate this is the start address
		 */
		if (argc < 7) {
			printf("Usage:  %s PGZ [32|24] OUTPUT.PGZ START SEG1.BIN ADDR1 ... SEGx.BIN ADDRx\n", argv[0]);
			return 1;
		}
		// Must specify 32 or 24 bit addressing.
		addr = atoi(argv[2]);
		if (addr != 24 && addr != 32) {
			printf("Addressing bits must be 24 or 32.\n");
			return 1;
		}
		// Must have argument pairs.
		if ((argc - 5) % 2 != 0) {
			printf("Must provide an even number of segment arguments.\n");
			return 1;
		}
		// Start of segment arguments.
		count = 5;
		// Open file to write.
		out = fopen(argv[3], "wb");
		if (!out) {
			printf("Unable to open output file.\n");
			return 1;
		}
		// Header.
		if (addr == 24) fputc('Z', out); else fputc('z', out);
		// Assemble segments.
		while (count < argc) {
			// Open segment to read.
			in = fopen(argv[count], "rb");
			if (!in) {
				fclose(out);
				printf("Unable to open segment %s.\n", argv[count]);
				return 1;
			}
			count++;
			// Get segment size.
			fseek(in, 0, SEEK_END);
			length = ftell(in);
			fseek(in, 0, SEEK_SET);
			// Write segment info.
			start = (int32_t)strtol(argv[count], NULL, 0);
			count++;
			if (addr == 24) {
				fwrite(&start, sizeof(char), 3, out);
				fwrite(&length, sizeof(char), 3, out);
			} else {
				fwrite(&start, sizeof(int32_t), 1, out);
				fwrite(&length, sizeof(int32_t), 1, out);
			}
			// Copy binary into output.
			while ((c = fgetc(in)) != EOF) fputc(c, out);
			fclose(in);
		}
		// Write start address.
		start = (int32_t)strtol(argv[4], NULL, 0);
		if (addr == 24) {
			fwrite(&start, 3, 1, out);
			fwrite(&reserved, 3, 1, out);
		} else {
			fwrite(&start, sizeof(int32_t), 1, out);
			fwrite(&reserved, sizeof(int32_t), 1, out);
		}
		fclose(out);
	}

	return 0;
}
