#ifndef _F256_RTC_H_
#define _F256_RTC_H_

//
// F256jr definitions for the real time clock (bq4802)
//

#define RTC_SECS   0xD690
#define RTC_SECS_ALRM   0xD691
#define RTC_MINS   0xD692
#define RTC_MINS_ALRM   0xD693
#define RTC_HOURS   0xD694
#define RTC_HOURS_ALRM   0xD695
#define RTC_DAY   0xD696
#define RTC_DAY_ALRM   0xD697
#define RTC_DAY_OF_WEEK   0xD698
#define RTC_MONTH   0xD699
#define RTC_YEAR   0xD69A

#define RTC_RATES   0xD69B
#define RTC_PI_0   0x00                  // Periodic Interrupt rates...
#define RTC_PI_30us   0x01
#define RTC_PI_61us   0x02
#define RTC_PI_122us   0x03
#define RTC_PI_244us   0x04
#define RTC_PI_488us   0x05
#define RTC_PI_976us   0x06
#define RTC_PI_1ms   0x07
#define RTC_PI_3ms   0x08
#define RTC_PI_7ms   0x09
#define RTC_PI_15ms   0x0A
#define RTC_PI_31ms   0x0B
#define RTC_PI_62ms   0x0C
#define RTC_PI_125ms   0x0D
#define RTC_PI_250ms   0x0E
#define RTC_PI_500ms   0x0F

#define RTC_ENABLES   0xD69C
#define RTC_ABE   0x01
#define RTC_PWRIE   0x02
#define RTC_PIE   0x04
#define RTC_AIE   0x08

#define RTC_FLAGS   0xD69D
#define RTC_BVF   0x01
#define RTC_PWRF   0x02
#define RTC_PF   0x04
#define RTC_AF   0x08

#define RTC_CTRL   0xD96E
#define RTC_DSE   0x01
#define RTC_24HR   0x02
#define RTC_STOP   0x04
#define RTC_UTI   0x08

#define RTC_CENTURY   0xD69F

#endif // _F256_RTC_H_
