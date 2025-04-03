#ifndef __KEYPAD4X4_H__
#define __KEYPAD4X4_H__

#include <8051.h>          // 8051 microcontroller header
#include "../type.h"       // Custom type definitions (likely contains u8, u16 etc.)
#include "../Delay/Delay.h"// Delay function declarations
#include "../system.h"

#define KEY_PORT P0

#define KEY11 '7'
#define KEY12 '8'
#define KEY13 '9'
#define KEY14 '%'

#define KEY21 '4'
#define KEY22 '5'
#define KEY23 '6'
#define KEY24 'X'

#define KEY31 '1'
#define KEY32 '2'
#define KEY33 '3'
#define KEY34 '-'

#define KEY41 'C'
#define KEY42 '0'
#define KEY43 '='
#define KEY44 '+'

u8 KEYPAD_GetCode(void);
u8 KEYPAD_GetKey(void);

#endif