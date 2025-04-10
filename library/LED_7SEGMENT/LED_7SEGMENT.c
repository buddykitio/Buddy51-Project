#include "LED_7SEGMENT.h"

cbyte SEG_LOOKUP[10] = {_0, _1, _2, _3, _4, _5, _6, _7, _8, _9};

 int strlen(const char *str) {
 int length = 0;
    while (str[length] != '\0') {
        length++;  // Increment the counter until the null terminator is found
    }
    return length;
}

 u8 SEG_BUFF[6] = {0, 0, 0, 0, 0, 0};
 u8 disPos = 0;

 void SEG_Loop(){
    // Optionally, reload timer value here to control blinking frequency

#if DISPLAY_TIMER
    TH1 = SEG_TIMER_TH;
    TL1 = SEG_TIMER_TL;
#else
    TH0 = SEG_TIMER_TH;
    TL0 = SEG_TIMER_TL;
#endif

    // Clear all segment control signals to turn off all segments initially
#if SEG_MODE
    SEG1 = SEG2 = SEG3 = SEG4 = SEG5 = SEG6 = 1;
#else
    SEG1 = SEG2 = SEG3 = SEG4 = SEG5 = SEG6 = 0;
#endif
  
    // Set the port to the value stored in the segment buffer for the current display position
    SEG_PORT = SEG_BUFF[disPos];
  
    // Activate the corresponding segment control based on the current display position
#if SEG_MODE
    SEG1 = (disPos != 0);
    SEG2 = (disPos != 1);
    SEG3 = (disPos != 2);
    SEG4 = (disPos != 3);
    SEG5 = (disPos != 4);
    SEG6 = (disPos != 5);
#else
    SEG1 = (disPos == 0);
    SEG2 = (disPos == 1);
    SEG3 = (disPos == 2);
    SEG4 = (disPos == 3);
    SEG5 = (disPos == 4);
    SEG6 = (disPos == 5);      
#endif
  
    // Increment the display position to move to the next segment
    disPos++;
  
    // Reset the display position if it exceeds the maximum segment index (5)
    if (disPos >= 6) {
        disPos = 0;
    }
}

 void SEG_Init(void) {
#if DISPLAY_TIMER
    // Configure Timer 0 Mode 2
    TMOD &= 0x0F;
    TMOD |= 0x10; // Set Timer 0 to Mode 1
    TH1 = SEG_TIMER_TH; // Example initial value
    TL1 = SEG_TIMER_TL;

    // Enable Timer 0 Interrupt
    TR1 = 1; // Start Timer 0
    ET1 = 1; // Enable Timer 0 interrupt
#else
    // Configure Timer 0 Mode 2
    TMOD &= 0xF0;
    TMOD |= 0x01; // Set Timer 0 to Mode 1
    TH0 = SEG_TIMER_TH; // Example initial value
    TL0 = SEG_TIMER_TL;

    // Enable Timer 0 Interrupt
    TR0 = 1; // Start Timer 0
    ET0 = 1; // Enable Timer 0 interrupt
#endif
    EA = 1; // Enable all interrupts
}

 void SEG_OutData(const char *datas) {
u8 i, d, decimalPos, startIndex, digitsToDisplay;
int j;
long dat = 0;     // Variable to hold the parsed number
decimalPos = -1;  // Position of the decimal point, default to -1 if no decimal
i = 6;            // Start from the last digit position (6-segment display)

    // If the number is negative, skip the first character when processing digits
    startIndex = 0;
    if (datas[0] == '-') {
        startIndex = 1;  // Start processing from the second character
        SEG_BUFF[0] = _MINUS;  // Place the minus sign at the first position
    }

    // Find the position of the decimal point if it exists
    for (j = startIndex; datas[j] != '\0'; j++) {
        if (datas[j] == '.') {
            decimalPos = j - (startIndex);  // Store the position relative to the number part
            break;
        }
    }

    // Convert the string number to a long integer (ignoring the decimal point)
    for (j = startIndex; datas[j] != '\0'; j++) {
        if (datas[j] != '.') {
            dat = dat * 10 + (datas[j] - '0');  // Convert the character to an integer
        }
    }

    // Number of digits to display (excluding the sign)
    digitsToDisplay = strlen(datas) - (datas[0] == '-' ? 1 : 0);  // Exclude the negative sign if present

    // Loop to extract each digit and store it in the segment buffer
    while (i && digitsToDisplay > 0) {
        i--;              // Decrement the buffer index to fill from right to left
        d = dat % 10;     // Extract the last digit of the number
        dat /= 10;        // Remove the last digit from the number
		
		if(i != 0 || datas[0] != '-') 
			SEG_BUFF[i] = SEG_LOOKUP[d];  // Store the corresponding 7-segment code for the digit

        // If the current position corresponds to where the decimal point should go, set it
       if (digitsToDisplay == decimalPos + 1) {
            SEG_BUFF[i] |= _DP;  // Set the decimal point on the segment
        }

        digitsToDisplay--;
    }

    //Fill remaining buffer positions with 0 to clear the display
    while (i) {
        i--;
		SEG_BUFF[i] = _SPACE;
	}
}
