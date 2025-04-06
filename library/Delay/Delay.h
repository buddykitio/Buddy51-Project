#ifndef _DELAY_H_  
#define _DELAY_H_ 

#include <8052.h>
#include "../type.h"
#include "../system.h"

#define _1MS_COUNT (MACHINE_CYCLE / 1000)  // Counts for 1ms delay

// Calculate THx and TLx values
#define TIMER_RELOAD (0xFFFF - _1MS_COUNT + 1)
#define THX ((TIMER_RELOAD >> 8) & 0xFF)  // High byte
#define TLX (TIMER_RELOAD & 0xFF)         // Low byte

void DelayXus(u8 xUs);
void DelayXms(u16 xMs); //uses timer 1/0

#endif