#include <8051.h> 
#include "../library/Delay/Delay.h"
#include "../library/LED_7SEGMENT/LED_7SEGMENT.h"

// Function to delay for approximately 1 second
void Delay1s() {
    unsigned int i;
    for (i = 0; i < 20000; i++) { // Adjust loop count based on your clock speed
        DelayXus(5);             // Small delay inside loop for better accuracy
    }
}

DISPLAY_INTERRUPT()

void main() {
    SEG_Init();
    while(1) {
        SEG_OutData("1234.5");
        Delay1s();
        SEG_OutData("-67.890");
        Delay1s();
    } 
}