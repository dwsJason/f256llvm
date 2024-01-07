#ifndef _F256JR_H_
#define _F256JR_H_

//
// I/O register address definitions
//

//;
//; MMU Registers
//;

#define MMU_MEM_CTRL   0x0000            // MMU Memory Control Register
#define MMU_IO_CTRL   0x0001             // MMU I/O Control Register
#define MMU_IO_PAGE_0   0x00
#define MMU_IO_PAGE_1   0x01
#define MMU_IO_TEXT   0x02
#define MMU_IO_COLOR   0x03
#define MMU_MEM_BANK_0   0x0008          // MMU Edit Register for bank 0 ($0000 - $1FFF)
#define MMU_MEM_BANK_1   0x0009          // MMU Edit Register for bank 1 ($2000 - $3FFF)
#define MMU_MEM_BANK_2   0x000A          // MMU Edit Register for bank 2 ($4000 - $5FFF)
#define MMU_MEM_BANK_3   0x000B          // MMU Edit Register for bank 3 ($6000 - $7FFF)
#define MMU_MEM_BANK_4   0x000C          // MMU Edit Register for bank 4 ($8000 - $9FFF)
#define MMU_MEM_BANK_5   0x000D          // MMU Edit Register for bank 5 ($A000 - $BFFF)
#define MMU_MEM_BANK_6   0x000E          // MMU Edit Register for bank 6 ($C000 - $DFFF)
#define MMU_MEM_BANK_7   0x000F          // MMU Edit Register for bank 7 ($E000 - $FFFF)

//;
//; Vicky Registers
//;

#define VKY_MSTR_CTRL_0   0xD000         // Vicky Master Control Register 0
#define VKY_MSTR_CTRL_1   0xD001         // Vicky Master Control Register 1

#define VKY_LAYER_CTRL_0   0xD002        // Vicky Layer Control Register 0
#define VKY_LAYER_CTRL_1   0xD003        // Vicky Layer Control Register 1

#define VKY_BRDR_CTRL   0xD004           // Vicky Border Control Register
#define VKY_BRDR_COL_B   0xD005          // Vicky Border Color -- Blue
#define VKY_BRDR_COL_G   0xD006          // Vicky Border Color -- Green
#define VKY_BRDR_COL_R   0xD007          // Vicky Border Color -- Red
#define VKY_BRDR_VERT   0xD008           // Vicky Border vertical thickness in pixels
#define VKY_BRDR_HORI   0xD009           // Vicky Border Horizontal Thickness in pixels

#define VKY_BKG_COL_B   0xD00D           // Vicky Graphics Background Color Blue Component
#define VKY_BKG_COL_G   0xD00E           // Vicky Graphics Background Color Green Component
#define VKY_BKG_COL_R   0xD00F           // Vicky Graphics Background Color Red Component

#define VKY_CRSR_CTRL   0xD010           // Vicky Text Cursor Control
#define VKY_CRSR_CHAR   0xD012
#define VKY_CRSR_X_L   0xD014            // Cursor X position
#define VKY_CRSR_X_H   0xD015
#define VKY_CRSR_Y_L   0xD016            // Cursor Y position
#define VKY_CRSR_Y_H   0xD017

#define VKY_LINE_CTRL   0xD018           // Control register for the line interrupt
#define VKY_LINE_ENABLE   0x01
#define VKY_LINE_NBR_L   0xD019          // Line number target low byte
#define VKY_LINE_NBR_H   0xD01A          // Line number target high byte


//;
//; Bitmap Registers
//;

#define VKY_BM0_CTRL   0xD100            // Bitmap #0 Control Register
#define VKY_BM0_ADDR_L   0xD101          // Bitmap #0 Address bits 7..0
#define VKY_BM0_ADDR_M   0xD102          // Bitmap #0 Address bits 15..8
#define VKY_BM0_ADDR_H   0xD103          // Bitmap #0 Address bits 17..16

#define VKY_BM1_CTRL   0xD108            // Bitmap #1 Control Register
#define VKY_BM1_ADDR_L   0xD109          // Bitmap #1 Address bits 7..0
#define VKY_BM1_ADDR_M   0xD10A          // Bitmap #1 Address bits 15..8
#define VKY_BM1_ADDR_H   0xD10B          // Bitmap #1 Address bits 17..16

#define VKY_BM2_CTRL   0xD110            // Bitmap #2 Control Register
#define VKY_BM2_ADDR_L   0xD111          // Bitmap #2 Address bits 7..0
#define VKY_BM2_ADDR_M   0xD112          // Bitmap #2 Address bits 15..8
#define VKY_BM2_ADDR_H   0xD113          // Bitmap #2 Address bits 17..16

#define VKY_TXT_FGLUT   0xD800           // Text foreground CLUT
#define VKY_TXT_BGLUT   0xD840           // Text background CLUT

//;
//; Color Lookup Tables (I/O Page 1)
//;

#define VKY_GR_CLUT_0   0xD000           // Graphics LUT #0
#define VKY_GR_CLUT_1   0xD400           // Graphics LUT #1
#define VKY_GR_CLUT_2   0xD800           // Graphics LUT #2
#define VKY_GR_CLUT_3   0xDC00           // Graphics LUT #3

//;
//; Buzzer and Status LEDs
//;

#define VKY_SYS0   0xD6A0
#define VKY_SYS1   0xD6A1

#define SYS_SID_ST   0x08
#define SYS_PSG_ST   0x04

//;
//; Software Reset
//;
#define VKY_RST0   0xD6A2 	//R/W  Set to 0xDE to enable software reset
#define VKY_RST1   0xD6A3 	//R/W  Set to 0xAD to enable software reset

//;
//; Random Numbers
//;
#define VKY_SEEDL 	   0xD6A4    // SEED[7. . . 0]
#define VKY_RNDL 	   0xD6A4    // RND[7. . . 0]
#define VKY_SEEDH 	   0xD6A5    // SEED[15. . . 0]
#define VKY_RNDH 	   0xD6A5    // RND[15. . . 0]
#define VKY_RND_CTRL   0xD6A6 	// SEED_LD=$2 ENABLE=$1
#define VKY_RND_STAT   0xD6A6 	// DONE=$80

//;
//; Machine ID and Version
//;
#define VKY_MID   0xD6A7			// Machine ID
#define VKY_PCBID0   0xD6A8		// "B"
#define VKY_PCBID1   0xD6A9      // "0"
#define VKY_CHSV0   0xD6AA       // TinyVicky subversion BCD (low)
#define VKY_CHSV1   0xD6AB  		// TinyVicky subversion in BCD (high)
#define VKY_CHV0   0xD6AC  		// TinyVicky version in BCD (low)
#define VKY_CHV1   0xD6AD  		// TinyVicky version in BCD (high)
#define VKY_CHN0   0xD6AE  		// TinyVicky number in BCD (low)
#define VKY_CHN1   0xD6AF  		// TinyVicky number in BCD (high)
#define VKY_PCBMA   0xD6EB  		// PCB Major Rev (ASCII)
#define VKY_PCBMI   0xD6EC  		// PCB Minor Rev (ASCII)
#define VKY_PCBD   0xD6ED  		// PCB Day (BCD)
#define VKY_PCBM   0xD6EE  		// PCB Month (BCD)
#define VKY_PCBY   0xD6EF  		// PCB Year (BCD)

#define MID_C256_FMX    = %00000
#define MID_C256_U      = %00001
#define MID_F256        = %00010
#define MID_F256_K      = %10010
#define MID_A2560_DEV   = %00011
#define MID_GEN_X       = %00100
#define MID_C256_U_PLUS = %00101
#define MID_A2560_X = %01000 
#define MID_A2560_U = %01001 
#define MID_A2560_M = %01010 
#define MID_A2560_K = %01011 

//;
//; Sound Generators
//;
#define VKY_PSG0   0xD600
#define VKY_PSG1   0xD610

#define VKY_PSG_BOTH   0xD608

//;
//; CODEC
//;
#define CODEC_LO           0xD620
#define CODEC_HI           0xD621
#define CODEC_CTRL         0xD622



#endif // _F256JR_H_
