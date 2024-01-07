#ifndef _F256_TIMERS_H_
#define _F256_TIMERS_H_

//
// Definitions for the interval timers and the RTC
//

// Timer 0 -- Based on system clock

#define TM0_CTRL   0xD650
#define TM_CTRL_ENABLE   0x01
#define TM_CTRL_CLEAR   0x02
#define TM_CTRL_LOAD   0x04
#define TM_CTRL_UP_DOWN   0x08
#define TM_CTRL_RECLEAR   0x10
#define TM_CTRL_RELOAD   0x20
#define TM_CTRL_INTEN   0x80

#define TM0_STAT   0xD650
#define TM_STAT_EQUAL   0x01

#define TM0_VALUE_L   0xD651
#define TM0_VALUE_M   0xD652
#define TM0_VALUE_H   0xD653

#define TM0_CMP_CTRL   0xD654
#define TM_CMP_CTRL_CLR   0x01
#define TM_CMP_CTRL_LOAD   0x02

#define TM0_CMP_L   0xD655
#define TM0_CMP_M   0xD656
#define TM0_CMP_H   0xD657

// Timer 1 -- Based on SOF

#define TM1_CTRL   0xD658
#define TM1_STAT   0xD658
#define TM1_VALUE_L   0xD659
#define TM1_VALUE_M   0xD65A
#define TM1_VALUE_H   0xD65B
#define TM1_CMP_CTRL   0xD65C
#define TM1_CMP_L   0xD65D
#define TM1_CMP_M   0xD65E
#define TM1_CMP_H   0xD65F

#endif // _F256_TIMERS_H_
