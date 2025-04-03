#ifndef __LED_7SEGMENT_H__
#define __LED_7SEGMENT_H__

#include <8051.h>          // 8051 microcontroller header
#include "../type.h"       // Custom type definitions (likely contains u8, u16 etc.)
#include "../Delay/Delay.h"// Delay function declarations
#include "../system.h"

#define SEG_MODE 0

#define SEG_PORT P0

#define SEG1 P2_0
#define SEG2 P2_1 
#define SEG3 P2_2
#define SEG4 P2_3
#define SEG5 P2_4
#define SEG6 P2_5

#define DISPLAY_TIMER 0


#define SEG_TIMER_TH 0xF1
#define SEG_TIMER_TL 0x4D

#if SEG_MODE
	#define _SEG _CA
	#define _SP(A , B) A & B
	#define _OP &
#else
	#define _SEG _CC
	#define _SP(A , B) A | B
	#define _OP |
#endif

#define _CC(a) a
#define _CA(a) ~a

#define _DP _SEG(0x80)
#define _SPACE _SEG(0x00)
#define _MINUS _SEG(0x40)

#define _0 _SEG(0x3F)
#define _1 _SEG(0x06)
#define _2 _SEG(0x5B)
#define _3 _SEG(0x4F)
#define _4 _SEG(0x66)
#define _5 _SEG(0x6D)
#define _6 _SEG(0x7D)
#define _7 _SEG(0x07)
#define _8 _SEG(0x7F)
#define _9 _SEG(0x6F)


int strlen(const char *str);
void SEG_Loop();
void SEG_Init(void);
void SEG_OutData(const char *datas);

#if DISPLAY_TIMER
#define DISPLAY_INTERRUPT()\
void Timer1_ISR(void) __interrupt (3)  __using(0){SEG_Loop();}
#else
#define DISPLAY_INTERRUPT()\
void Timer0_ISR(void) __interrupt (1)  __using(0){SEG_Loop();}
#endif

#endif