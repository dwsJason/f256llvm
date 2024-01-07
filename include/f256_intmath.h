#ifndef _F256_INTMATH_H_
#define _F256_INTMATH_H_

//
// Integer Math Coprocessor
//

#define MULU_A_L   0xDE00 //R/W  Unsigned A Low Byte
#define MULU_A_H   0xDE01 //R/W  Unsigned A High Byte
#define MULU_B_L   0xDE02 //R/W  Unsigned B Low Byte
#define MULU_B_H   0xDE03 //R/W  Unsigned B High Byte
#define MULU_LL   0xDE10 //R  ? × ? (unsigned) byte 0
#define MULU_LH   0xDE11 //R  ? × ? (unsigned) byte 1
#define MULU_HL   0xDE12 //R  ? × ? (unsigned) byte 2
#define MULU_HH   0xDE13 //R  ? × ? (unsigned) byte 3
#define DIVU_DEN_L   0xDE04 //R/W  Unsigned Denominator Low Byte
#define DIVU_DEN_H   0xDE05 //R/W  Unsigned Denominator High Byte
#define DIVU_NUM_L   0xDE06 //R/W  Unsigned Numerator Low Byte
#define DIVU_NUM_H   0xDE07 //R/W  Unsigned Numerator High Byte
#define QUOU_LL   0xDE14 //R  Quotient of NUM/DEN (unsigned) low byte
#define QUOU_LH   0xDE15 //R  Quotient of NUM/DEN (unsigned) high byte
#define REMU_HL   0xDE16 //R  Remainder of NUM/DEN (unsigned) low byte
#define REMU_HH   0xDE17 //R  Remainder of NUM/DEN (unsigned) low byte
#define ADD_A_LL   0xDE08 //R/W  Unsigned A byte 0
#define ADD_A_LH   0xDE09 //R/W  Unsigned A byte 1
#define ADD_A_HL   0xDE0A //R/W  Unsigned A byte 2
#define ADD_A_HH   0xDE0B //R/W  Unsigned A byte 3
#define ADD_B_LL   0xDE0C //R/W  Unsigned B byte 0
#define ADD_B_LH   0xDE0D //R/W  Unsigned B byte 1
#define ADD_B_HL   0xDE0E //R/W  Unsigned B byte 2
#define ADD_B_HH   0xDE0F //R/W  Unsigned B byte 3
#define ADD_R_LL   0xDE18 //R  ? + ? (unsigned) byte 0
#define ADD_R_LH   0xDE19 //R  ? + ? (unsigned) byte 1
#define ADD_R_HL   0xDE1A //R  ? + ? (unsigned) byte 2
#define ADD_R_HH   0xDE1B //R  ? + ? (unsigned) byte 3

#endif // _F256_INTMATH_H_
