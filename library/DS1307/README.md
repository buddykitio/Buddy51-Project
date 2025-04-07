# RTC (DS1307) Library for 8051 (SDCC)

This library provides functions to interface with the **DS1307 Real-Time Clock (RTC)** using an **8051 microcontroller** with **SDCC**. It allows reading and writing time and date, as well as accessing the RTC's RAM storage.

---

## 📌 **Constants**
| Constant | Value | Description |
|----------|-------|-------------|
| `DS1307` | `0xD0` | I2C address of the DS1307 RTC |
| `RAM_OFFSET` | `0x08` | Starting address of user RAM in DS1307 |
| `IS_LEAP_YEAR(y)` | Macro | Determines if a given year is a leap year |

---

## 📌 **Functions**
| Function | Description |
|----------|-------------|
| `void RTC_Init(void);` | Initializes the RTC module. |
| `u8 RTC_Read(void);` | Reads the current time and date from the RTC module. |
| `void RTC_Write(void);` | Writes the stored time and date variables to the RTC module. |
| `void RTC_Time2Str(u8* str);` | Converts the current time into a string format (HH:MM:SS). |
| `void RTC_Date2Str(u8* str);` | Converts the current date into a string format (DD/MM/YY). |
| `u16 getDayOfYear(void);` | Calculates the day number in the current year (1-365/366). |
| `void RTC_WriteData(u8 addr, u8 dat);` | Writes a byte to the RTC’s user RAM. |
| `u8 RTC_ReadData(u8 addr);` | Reads a byte from the RTC’s user RAM. |

---

## 📌 **Dependencies**
This library depends on the following modules:
- **[I2C Library](../I2C/README.md)** (for communication with the DS1307)
- **[Delay Library](../Delay/README.md)** (for accurate timing)

Ensure these libraries are included in your project.

---

## 📌 **Example: Display Time on LCD**

This example initializes the RTC and continuously updates the **LCD display** with the current time.

```c
#include "../I2C/I2C.h"
#include "../LCD4/LCD4.h"
#include "../DS1307/DS1307.h"
#include "../Delay/Delay.h"

void main() {
    u8 buff[17];

    I2C_Init();    // Initialize I2C
    LCD_Init();    // Initialize LCD
    RTC_Init();    // Initialize RTC

    LCD_LeftToRight();   // Default: Left-to-right text
    LCD_NoAutoscroll();  // Disable autoscroll (manual scrolling only)

    LCD_Puts("RTC CLOCK DEMO");

    while (1) { // Infinite loop
        RTC_Read();          // Read current time from RTC
        RTC_Time2Str(buff);  // Convert time to string format
        LCD_ClearRow(0);     // Clear first row of LCD
        LCD_Puts(buff);      // Display time on LCD

        Delay1s();           // Wait 1 second before updating again
    }
}
```

## 📢 Notes
This library is designed for SDCC-based 8051 microcontrollers.

Modify I2C pin assignments in the I2C library if needed.

Ensure the DS1307 module is powered and has a backup battery for accurate timekeeping.