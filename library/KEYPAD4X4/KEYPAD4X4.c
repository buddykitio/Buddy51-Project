#include "KEYPAD4X4.h"

#define KEY_MASK 0xF0

static u8 KEYPAD_GetCode(void){
u8 key;
    KEY_PORT = KEY_MASK;
    _nop_();

	if(KEY_PORT == KEY_MASK)   // No key pressed
		return 0;
    
    KEY_PORT = B11111110;
    _nop_();
    key = KEY_PORT & KEY_MASK;
    if(key != KEY_MASK){
        if(!(key & B00010000)) return 1;
        if(!(key & B00100000)) return 2;
        if(!(key & B01000000)) return 3;
        if(!(key & B10000000)) return 4;
    }

    KEY_PORT = B11111101;
    _nop_();
    key = KEY_PORT & KEY_MASK;
    if(key != KEY_MASK){
        if(!(key & B00010000)) return 5;
        if(!(key & B00100000)) return 6;
        if(!(key & B01000000)) return 7;
        if(!(key & B10000000)) return 8;
    }

    KEY_PORT = B11111011;
    _nop_();
    key = KEY_PORT & KEY_MASK;
    if(key != KEY_MASK){
        if(!(key & B00010000)) return 9;
        if(!(key & B00100000)) return 10;
        if(!(key & B01000000)) return 11;
        if(!(key & B10000000)) return 12;
    }

    KEY_PORT = B11110111;
    _nop_();
    key = KEY_PORT & KEY_MASK;
    if(key != KEY_MASK){
        if(!(key & B00010000)) return 13;
        if(!(key & B00100000)) return 14;
        if(!(key & B01000000)) return 15;
        if(!(key & B10000000)) return 16;
    }

    return 0;
}

cbyte KEY_LOOKUP[] = {
    KEY11, KEY12, KEY13, KEY14,
    KEY21, KEY22, KEY23, KEY24,
    KEY31, KEY32, KEY33, KEY34,
    KEY41, KEY42, KEY43, KEY44
};

// Variable to store the last key pressed (for debouncing)
static u8 lastKey;

// Function to get the key pressed with debounce
static u8 KEYPAD_GetKey(void){
	u8 curKey;
	curKey = KEYPAD_GetCode();  // Get the current key pressed

	// If the current key is the same as the last one, ignore it (debouncing)
	if(curKey == lastKey || !curKey)
		return 0;
	
	lastKey = curKey;  // Update last key pressed
	DelayXms(5);    // Debounce delay
	return KEY_LOOKUP[curKey - 1];     // Return the new key pressed
}
