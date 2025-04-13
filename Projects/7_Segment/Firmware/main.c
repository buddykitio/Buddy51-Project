#include <8051.h>
#include "../library/Delay/Delay.h"

#define KEY P2_6
cbyte SEG_LOOKUP[10] = {0XC0, 0XF9, 0XA4, 0XB0,  0X99, 0X92, 0X82, 0XF8, 0X80, 0X90};

void delay(unsigned int ms) {
    unsigned int i, j;
    for(i=0; i<ms; i++)
        for(j=0; j<1275; j++);
}

void main() {
u8 count = 0;
KEY = 1;
    while(1) {
        if(!KEY){
            DelayXms(200);
        while(!KEY)
        DelayXms(200);
    count++;
    }
    if(count > 9)
    count = 0;
P0 = SEG_LOOKUP[count];
    }

}