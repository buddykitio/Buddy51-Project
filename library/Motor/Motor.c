#include "Motor.h"

// Wait for servo pulse delay based on angle and phase (0 = ON, 1 = OFF)
void waitServoPulse(u16 angle, u8 isOff) {
    u16 pulseWidth, ticks;

    // Clamp angle to 0–180
    if (angle > 180)
        angle = 180;

    // Setup Timer 1 in 16-bit mode
    TMOD &= 0x0F;   // Clear Timer 1 bits
    TMOD |= 0x10;   // Set Timer 1 to Mode 1 (16-bit)

    // Compute pulse width in microseconds
    pulseWidth = 500 + ((u32)angle * 2000) / 180;

    // Adjust for ON or OFF duration
    if (isOff)
        pulseWidth = 20000 - pulseWidth;

    // Convert us to timer ticks (ticks ≈ us * 59 / 64)
    ticks = 65536 - (((u32)pulseWidth * 59) >> 6);

    // Load Timer 1 with calculated ticks
    TR1 = 0;                    // Stop Timer 1
    TH1 = ticks >> 8;
    TL1 = ticks & 0xFF;
    TF1 = 0;                    // Clear overflow flag
    TR1 = 1;                    // Start timer

    while (!TF1);               // Wait until time expires

    TR1 = 0;                    // Stop Timer
    TF1 = 0;                    // Clear overflow flag
}
