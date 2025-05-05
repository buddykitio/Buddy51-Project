#ifndef TIMER_H
#define TIMER_H


#include "../system.h"
#include <8051.h>
#include "../type.h"


// Timer selection
#define TIMER0 0
#define TIMER1 1

// Timer functions
void timer_init(u8 timer);
void timer_start(u8 timer, uint reload_val);
uint timer_calc(unsigned long ms, unsigned long freq);

// ISR declarations (SDCC format)
void timer0_isr(void) __interrupt(1);
void timer1_isr(void) __interrupt(3);

// Shared counter variables
extern volatile unsigned int timer0_ticks;
extern volatile unsigned int timer1_ticks;
#endif
