# EEPROM Library

This library provides functions to read from and write to an **I2C-based EEPROM (24LC16)** using an **8051 microcontroller** with **SDCC**.

---

## 📌 **Constants**
| Constant | Value | Description |
|----------|-------|-------------|
| `IC24LC16` | `0xA0` | EEPROM device address for 24LC16 |

---

## 📌 **Functions**
| Function | Description |
|----------|-------------|
| `u8 EEPROM_Goto(const u8 address, u8 mode);` | Sets the EEPROM's internal address pointer (used internally). |
| `u8 EEPROM_Write(u8 address, u8 data);` | Writes a single byte to a specified EEPROM address. |
| `u8 EEPROM_Read(u8 address, u8* data);` | Reads a single byte from a specified EEPROM address. |
| `u8 EEPROM_Writes(u8 address, void* vData, u8 length);` | Writes multiple bytes to EEPROM starting from the given address. |
| `u8 EEPROM_Reads(u8 address, void* vData, u8 length);` | Reads multiple bytes from EEPROM starting from the given address. |

---

## 📌 **Example: Test EEPROM Read/Write**

This example writes a byte to EEPROM and reads it back. If the written and read values match, it blinks an LED connected to **P1_1**.

```c
#include "EEPROM.h"

#define EEPROM_TEST_ADDRESS  0x10  // Test EEPROM address
#define TEST_VALUE           0x55  // Test data to write
#define LED_PIN              P1_1  // LED connected to P1_1

void BlinkLED() {
    for (u8 i = 0; i < 5; i++) {  // Blink 5 times
        LED_PIN = 1;  
        DelayXms(500);
        LED_PIN = 0;
        DelayXms(500);
    }
}

void main() {
    u8 readData;

    I2C_Init();  // Initialize I2C
    LED_PIN = 0; // Turn off LED initially

    // Write test value to EEPROM
    if (EEPROM_Write(EEPROM_TEST_ADDRESS, TEST_VALUE) == 0) {
        DelayXms(10);  // Wait for EEPROM write cycle
    }

    // Read back the value
    if (EEPROM_Read(EEPROM_TEST_ADDRESS, &readData) == 0) {
        // If read value matches the written value, blink LED
        if (readData == TEST_VALUE) {
            BlinkLED();
        }
    }

    while (1); // Infinite loop
}

---

## 📢 **Notes**
- This library uses the **I2C Library** for communication.
- Designed for **SDCC-based 8051 microcontrollers**.
- Modify the **I2C pin assignments** in the **I2C library** if required.
