#ifndef _F256_XYMATH_H_
#define _F256_XYMATH_H_

//
// Registers for the bitmap coordinate math block
//

#define XY_BASE   0xD301         // Starting address of the bitmap
#define XY_POS_X   0xD304        // X-coordinate desired
#define XY_POS_Y   0xD306        // Y-coordinate desired
#define XY_OFFSET   0xD308       // Offset within an MMU bank of the pixel for (X, Y)
#define XY_BANK   0xD30A         // MMU bank containing the pixel for (X, Y)
#define XY_ADDRESS   0xD30B      // System address of the pixel for (X, Y)

#endif // _F256_XYMATH_H_
