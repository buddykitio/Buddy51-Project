#include <8051.h> 
#include "../library/LCD4/LCD4.h"
#include "../library/Delay/Delay.h"
#include "../library/DS1307/DS1307.h"

// Function to delay for approximately 1 second
void Delay1s() {
    unsigned int i;
    for (i = 0; i < 20000; i++) { // Adjust loop count based on your clock speed
        DelayXus(5);             // Small delay inside loop for better accuracy
    }
}

void main() {
u8 buff[17];

    I2C_Init();
    LCD_Init();
    LCD_LeftToRight();   // Default: Left-to-right text
    LCD_NoAutoscroll();  // Disable autoscroll (manual scrolling only)
    
    // Display a long string to enable scrolling
    LCD_Puts("HI BUDDIES!");
    
    while (1) { // Infinite loop
        // Scroll right 4 times (1-second delay between each)
        RTC_Read();
        RTC_Time2Str(buff);
        LCD_ClearRow(0);
        LCD_Puts(buff);

        Delay1s();
    }
}