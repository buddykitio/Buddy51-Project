# 4x4 Matrix Keypad Library

This library provides functions to interface with a 4x4 matrix keypad on 8051 microcontrollers using SDCC.

---

## 📌 **Functions**
| Function | Description |
|----------|-------------|
| `u8 KEYPAD_GetCode(void);` | Returns the raw keycode pressed. |
| `u8 KEYPAD_GetKey(void);` | Returns the corresponding character for the key pressed, with debounce handling. |

---

## 📢 **Key Mapping**
Each key press returns a keycode, which is then mapped to a corresponding character. Users can modify these mappings in `KEYPAD4X4.h` based on their application needs. 

By default, the library uses the following key mappings:

```c
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
```

Additionally, users may **customize the keypad port** by modifying:

```c
#define KEY_PORT P0
```

---

## 📢 **Example Code**
The following example demonstrates how to read key presses from the 4x4 keypad:

```c
#include <8051.h> 
#include "../library/LCD4/LCD4.h"
#include "../library/Delay/Delay.h"
#include "../library/KEYPAD4X4/KEYPAD4X4.h"

// Function to delay for approximately 1 second
void Delay1s(void) {
    unsigned int i;
    for (i = 0; i < 20000; i++) {
        DelayXus(5);
    }
}

void main(void) {
    u8 key;

    LCD_Init();   
    LCD_Puts("HI BUDDIES!");
   
    while (1) {
        key = KEYPAD_GetKey();
        if(key){
            LCD_Goto(2, 0);
            LCD_Data(key);
        }
    }
}
```

---

## 📣 **Important Notes**
- The **default key mapping can be modified** in `KEYPAD4X4.h` as per user requirements.
- Users can customize the **keypad port** by modifying `#define KEY_PORT P0`.
- This library is designed for SDCC-based 8051 microcontrollers.
- Refer to the source code for detailed implementation.

