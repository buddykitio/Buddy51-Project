#include "Motor.h"

// MoveServo - Generates a single PWM pulse corresponding to the specified angle (0–180°)
// Compatible with standard hobby servos (typically 1ms to 2ms pulse width in a 20ms frame)

// Generate ON duration based on servo angle (0-180 degrees)
void waitServoOnPulse(u16 angle) {
    u16 pulseWidth, onTime;

    if (angle > 180)
        angle = 180;
    
    TMOD &= 0x0F;   // Clear lower 4 bits for Timer 0
    TMOD |= 0x10;   // Set Mode 1 (16-bit)
    
    // Convert angle to pulse width: 500us (0°) to 2500us (180°)
    pulseWidth = 500 + ((u32)angle * 2000) / 180;

    // Convert microseconds to timer ticks (approx. ticks = us * 59 / 64)
    onTime = 65536 - (((u32)pulseWidth * 59) >> 6);

    // Setup Timer 0 for ON duration
    TR1 = 0;                    // Stop Timer 0
    TH1 = onTime >> 8;
    TL1 = onTime & 0xFF;
    TF1 = 0;                    // Clear overflow flag
    TR1 = 1;                    // Start timer

    while (!TF1);               // Wait until ON time over

    TR1 = 0;                    // Stop Timer
    TF1 = 0;                    // Clear flag
}

// Generate OFF duration based on servo angle
void waitServoOffPulse(u16 angle) {
    u16 pulseWidth, offTime;

    if (angle > 180)
        angle = 180;
        
    TMOD &= 0x0F;   // Clear lower 4 bits for Timer 0
    TMOD |= 0x10;   // Set Mode 1 (16-bit)
    // Calculate pulse width again
    pulseWidth = 500 + ((u32)angle * 2000) / 180;

    // OFF time = 20000us - ON pulse width
    offTime = 65536 - (((u32)(20000 - pulseWidth) * 59) >> 6);

    // Setup Timer 0 for OFF duration
    TR1 = 0;
    TH1 = offTime >> 8;
    TL1 = offTime & 0xFF;
    TF1 = 0;
    TR1 = 1;

    while (!TF1);               // Wait until OFF time over

    TR1 = 0;
    TF1 = 0;
}
