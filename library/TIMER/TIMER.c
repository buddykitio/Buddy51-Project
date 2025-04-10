#include "timer.h"

// Define the counters
volatile unsigned int timer0_ticks = 0;
volatile unsigned int timer1_ticks = 0;

void timer_init(u8 timer) {
    if(timer == TIMER0) {
        TMOD |= 0x01;  // Timer 0, Mode 1
    } else { // TIMER1
        TMOD |= 0x10;  // Timer 1, Mode 1
    }
}

void timer_start(u8 timer, uint reload_val) {
    if(timer == TIMER0) {
        TH0 = (reload_val >> 8) & 0xFF;
        TL0 = reload_val & 0xFF;
        ET0 = 1;  // Enable Timer 0 interrupt
        EA = 1;   // Global interrupt enable
        TR0 = 1;  // Start timer
    } else { // TIMER1
        TH1 = (reload_val >> 8) & 0xFF;
        TL1 = reload_val & 0xFF;
        ET1 = 1;  // Enable Timer 1 interrupt
        EA = 1;   // Global interrupt enable
        TR1 = 1;  // Start timer
    }
}

uint timer_calc(unsigned long ms, unsigned long freq) {
    unsigned long cycles = (freq/12) * ms / 1000;
    return 65536 - cycles;
}

// Timer 0 ISR Implementation
void timer0_isr(void) __interrupt(1) {
    timer0_ticks++;
    TF0 = 0;  // Clear overflow flag
    // Reload if using Mode 1 (16-bit)
    TH0 = timer_calc(50, 11059200) >> 8;
    TL0 = timer_calc(50, 11059200) & 0xFF;
}

// Timer 1 ISR Implementation (MUST be present if declared)
void timer1_isr(void) __interrupt(3) {
    timer1_ticks++;
    TF1 = 0;  // Clear overflow flag
    // Reload if using Mode 1 (16-bit)
    TH1 = timer_calc(50, 11059200) >> 8;
    TL1 = timer_calc(50, 11059200) & 0xFF;
}