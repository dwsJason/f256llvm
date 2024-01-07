#ifndef _F256_DMA_H_
#define _F256_DMA_H_

//
// Registers for DMA
//

#define DMA_CTRL   0xDF00                // DMA Control Register
#define DMA_CTRL_START   0x80            // Start the DMA operation
#define DMA_CTRL_INT_EN   0x08           // Enable DMA interrupts
#define DMA_CTRL_FILL   0x04             // DMA is a fill operation (otherwise DMA is a copy)
#define DMA_CTRL_2D   0x02               // DMA is 2D operation (otherwise it is 1D)
#define DMA_CTRL_ENABLE   0x01           // DMA engine is enabled

#define DMA_STATUS   0xDF01              // DMA status register (Read Only)
#define DMA_STAT_BUSY   0x80             // DMA engine is busy with an operation

#define DMA_FILL_VAL   0xDF01            // Byte value to use for fill operations

#define DMA_SRC_ADDR   0xDF04            // Source address (system bus) for copy operations
#define DMA_DST_ADDR   0xDF08            // Destination address (system bus) for fill and copy operations

#define DMA_COUNT   0xDF0C               // Number of bytes to fill or copy (1D operations, 24 bit value)
#define DMA_WIDTH   0xDF0C               // Width of rectangle to fill or copy (2D operations, 16 bit value)
#define DMA_HEIGHT   0xDF0E              // Height of rectangle to fill or copy (2D operations, 16 bit value)
#define DMA_STRIDE_SRC   0xDF10          // Width of the source bitmap image in bytes (2D operations, 16 bit value)
#define DMA_STRIDE_DST   0xDF12          // Width of the destination bitmap image in bytes (2D operations, 16 bit value)

#endif // _F256_DMA_H_
