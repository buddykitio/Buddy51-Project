#include <8051.h>  // Include standard 8051 register definitions

// Delay function
void delay() {
    unsigned int i;
    for (i = 0; i < 30000; i++);  // Simple delay loop
}

void main() {
    P1 = 0x00;  // Set Port 1 as output (if required)

    while (1) {
        P1_0 = 1;  // Turn LED ON (assuming LED is connected to P1.0)
        delay();
        P1_0 = 0;  // Turn LED OFF
        delay();
    }
}
