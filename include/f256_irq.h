#ifndef _F256_IRQ_H_
#define _F256_IRQ_H_

//
// Interrupt Controller Registers
//
#define INT_PEND_0   0xD660  // Pending register for interrupts 0 - 7
#define INT_PEND_1   0xD661  // Pending register for interrupts 8 - 15
#define INT_MASK_0   0xD66C  // Mask register for interrupts 0 - 7
#define INT_MASK_1   0xD66D  // Mask register for interrupts 8 - 15

//
// Interrupt bits
//
#define INT00_VKY_SOF   0x01
#define INT01_VKY_SOL   0x02
#define INT02_PS2_KBD   0x04
#define INT03_PS2_MOUSE   0x08
#define INT04_TIMER_0   0x10
#define INT05_TIMER_1   0x20
#define INT06_DMA   0x40
#define INT07_RESERVED   0x80

#define INT10_UART   0x01
#define INT11_VKY_2   0x02
#define INT12_VKY_3   0x04
#define INT13_VKY_4   0x08
#define INT14_RTC   0x10
#define INT15_VIA   0x20
#define INT16_IEC   0x40
#define INT17_SDC_INSERT   0x80

#endif // _F256_IRQ_H_
