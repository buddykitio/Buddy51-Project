#include "Motor.h"

// MoveServo - Generates a single PWM pulse corresponding to the specified angle (0–180°)
// Compatible with standard hobby servos (typically 1ms to 2ms pulse width in a 20ms frame)
// Uses Timer 0 in 16-bit mode to generate precise timing delays
// Assumes a 12 MHz clock and 1T mode (Timer tick = 1.085 µs)

// Generate ON duration based on servo angle (0-180 degrees)
void waitServoOnPulse(u16 angle) {
    u16 pulseWidth, onTime;

    if (angle > 180)
        angle = 180;

    // Convert angle to pulse width: 500us (0°) to 2500us (180°)
    pulseWidth = 500 + ((u32)angle * 2000) / 180;

    // Convert microseconds to timer ticks (approx. ticks = us * 59 / 64)
    onTime = 65536 - (((u32)pulseWidth * 59) >> 6);

    // Setup Timer 0 for ON duration
    TR0 = 0;                    // Stop Timer 0
    TH0 = onTime >> 8;
    TL0 = onTime & 0xFF;
    TF0 = 0;                    // Clear overflow flag
    TR0 = 1;                    // Start timer

    while (!TF0);               // Wait until ON time over

    TR0 = 0;                    // Stop Timer
    TF0 = 0;                    // Clear flag
}

// Generate OFF duration based on servo angle
void waitServoOffPulse(u16 angle) {
    u16 pulseWidth, offTime;

    if (angle > 180)
        angle = 180;

    // Calculate pulse width again
    pulseWidth = 500 + ((u32)angle * 2000) / 180;

    // OFF time = 20000us - ON pulse width
    offTime = 65536 - (((u32)(20000 - pulseWidth) * 59) >> 6);

    // Setup Timer 0 for OFF duration
    TR0 = 0;
    TH0 = offTime >> 8;
    TL0 = offTime & 0xFF;
    TF0 = 0;
    TR0 = 1;

    while (!TF0);               // Wait until OFF time over

    TR0 = 0;
    TF0 = 0;
}
