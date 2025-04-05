#include <8051.h>
#define LED P1_1

void delay(unsigned int ms) {
    unsigned int i, j;
    for(i=0; i<ms; i++)
        for(j=0; j<1275; j++);
}

void main() {
    while(1) {
        LED = 0;    // LED ON
        delay(500);
        LED = 1;    // LED OFF
        delay(500);
    }
}