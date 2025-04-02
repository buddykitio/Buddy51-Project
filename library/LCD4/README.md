# LCD 4-bit Library

## 📌 Pin Connections

### LCD Pin Configuration (4-bit mode)

| LCD Pin | 8051 Connection | Description                    |
|---------|-----------------|--------------------------------|
| VSS     | GND             | Ground connection              |
| VDD     | +5V             | Power supply (5V)              |
| V0      | Potentiometer   | Contrast control (10kΩ pot)    |
| RS      | P2.2            | Register Select (0=cmd, 1=data)|
| RW      | GND             | Always write mode              |
| EN      | P2.3            | Enable pulse                   |
| D4      | P2.4            | Data bit 4                     |
| D5      | P2.5            | Data bit 5                     |
| D6      | P2.6            | Data bit 6                     |
| D7      | P2.7            | Data bit 7                     |
| A/K     | +5V via resistor| Backlight anode (if available) |

### LCD Pin Configuration (I2C Mode with PCF8574)

| LCD Pin | PCF8574 Pin | Description                     |
|---------|------------|---------------------------------|
| VSS     | GND        | Ground connection               |
| VDD     | +5V        | Power supply (5V)               |
| V0      | Potentiometer | Contrast control (10kΩ pot) |
| RS      | P0         | Register Select                 |
| RW      | GND        | Always write mode               |
| EN      | P2         | Enable pulse                    |
| D4      | P4         | Data bit 4                      |
| D5      | P5         | Data bit 5                      |
| D6      | P6         | Data bit 6                      |
| D7      | P7         | Data bit 7                      |
| A/K     | +5V via resistor | Backlight anode (if available) |

---

## 📌 Constants in LCD.H

### Command Constants

| Constant            | Value | Description                          |
|---------------------|-------|--------------------------------------|
| `LCD_CLEAR`         | 0x01  | Clears display and homes cursor      |
| `LCD_HOME`          | 0x02  | Returns cursor to home position      |
| `LCD_ENTRYMODESET`  | 0x04  | Sets text entry mode                 |
| `LCD_DISPLAYCTRL`   | 0x08  | Controls display on/off, cursorblink |
| `LCD_CURSORSHIFT`   | 0x10  | Controls cursor/display shifting     |
| `LCD_FUNCTIONSET`   | 0x20  | Sets interface, lines, and font      |

### Mode Flags

| Flag                | Value | Usage                                |
|---------------------|-------|--------------------------------------|
| `LCD_ENTRYLEFT`     | 0x02  | Left-to-right text direction         |
| `LCD_ENTRYSHIFTINC` | 0x01  | Auto-increment cursor position       |
| `LCD_DISPLAYMOVE`   | 0x08  | Move display instead of cursor       |
| `LCD_DISPLAYON`     | 0x04  | Turns display on                     |
| `LCD_4BITMODE`      | 0x00  | 4-bit interface mode                 |
| `LCD_2LINE`         | 0x08  | 2-line display mode                  |

---

## 📌 Functions in LCD.H

### Core Functions

| Function                 | Parameters          | Description                          |
|--------------------------|---------------------|--------------------------------------|
| `LCD_Command(u8 cmd)`    | cmd: command byte   | Sends command to LCD                 |
| `LCD_Data(u8 dat)`       | dat: data byte      | Sends data to LCD                    |
| `LCD_Init(void)`         | None                | Initializes LCD in 4-bit or I2C mode |

### Display Control

| Function                 | Description                          |
|--------------------------|--------------------------------------|
| `LCD_Puts(const char*)`  | Prints null-terminated string        |
| `LCD_Goto(u8 row, u8 col)` | Moves cursor to specified position |
| `LCD_Clear(u8, u8, u8)`  | Clears portion of display            |

### Scrolling Functions

| Function                 | Description                          |
|--------------------------|--------------------------------------|
| `LCD_ScrollLeft(void)`   | Shifts display left (RAM unchanged)  |
| `LCD_ScrollRight(void)`  | Shifts display right (RAM unchanged) |

### Text Direction

| Function                 | Description                          |
|--------------------------|--------------------------------------|
| `LCD_LeftToRight(void)`  | Sets left-to-right text flow         |
| `LCD_RightToLeft(void)`  | Sets right-to-left text flow         |

### Autoscroll Control

| Function                 | Description                          |
|--------------------------|--------------------------------------|
| `LCD_Autoscroll(void)`   | Enables auto-shifting of text        |
| `LCD_NoAutoscroll(void)` | Disables auto-shifting               |

---

## 📌 **Dependencies**
This library depends on the following modules:
- **[Delay Library](../Delay/README.md)** (for accurate timing)
- **[I2C Library](../I2C/README.md)** (for I2C-based LCD operation)

---

## 📌 **Note: Enabling I2C or Parallel Mode**
To choose between I2C or parallel mode, modify the `I2C_LCD` macro in your code:

- **Enable I2C Mode:** Set `#define I2C_LCD 1` and ensure the PCF8574 module is connected via I2C.
- **Enable Parallel Mode:** Set `#define I2C_LCD 0` and connect the LCD directly to the 8051 pins.

---

## Usage Example

### Example
```c
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
```
