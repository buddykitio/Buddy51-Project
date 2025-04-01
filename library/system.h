#ifndef _SYSTEM_H_
#define _SYSTEM_H_

// Define your system clock frequency (e.g., 12MHz)
#define CPU_CLK 11059200UL
#define MACHINE_CYCLE (CPU_CLK / 12)  // Machine cycle frequency

// if you want to change timer 0 for 1 millisecond delay, change here below
#define DELAY_TIMER 1


#endif