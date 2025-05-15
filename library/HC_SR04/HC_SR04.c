#include <8052.h> 
#include "HC_SR04.h"
#include "../Delay/Delay.h"
#include <stdio.h>  

int getDistance() {
    u32 time;

    // Configure Timer in Mode 1 (16-bit)
    TMOD &= 0x0F;   // Clear Timer
    TMOD |= 0x10;   // Timer mode 1 (16-bit)

    TR1 = 0;  // Stop Timer
    TF1 = 0;  // Clear overflow flag
    TH1 = 0;
    TL1 = 0;
    // Send 10us Trigger Pulse
    TRIG = 1;
    DelayXus(10);
    TRIG = 0;

    // Start Timer to wait for ECHO HIGH
    TR1 = 1;

    while (ECHO == 0) {
        if (TF1) {
            TR1 = 0; // Stop timer
            return -1; // Timeout: ECHO never went HIGH
        }
    }

    // // ECHO went HIGH — measure pulse width
    TR1 = 0;  // Stop Timer
    TF1 = 0;  // Clear overflow flag
    TH1 = 0;
    TL1 = 0;
    TR1 = 1;

    // Wait for ECHO to go LOW or timeout
    while (ECHO == 1 && TF1 == 0);

    TR1 = 0;

    if (TF1) {
        return -1; // Timeout: ECHO stuck HIGH
    }

    // Read Timer value
    time = (TH1 << 8) | TL1;

    time *= 217;
    time /= 11600;

    if(time > 400){
        time = 400;
    }

    return time;
}