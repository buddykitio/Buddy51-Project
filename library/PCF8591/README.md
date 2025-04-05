# PCF8591 Library

This library provides essential functions to interface with the PCF8591 ADC/DAC module using I2C communication on 8051 microcontrollers.

---

## 📌 **Definitions**
| Definition | Value | Description |
|------------|-------|-------------|
| `PCF8591_ADDR` | 0x90 | Default I2C address of PCF8591 |
| `AIN0` | 0x00 | Analog input channel 0 |
| `AIN1` | 0x01 | Analog input channel 1 |
| `AIN2` | 0x02 | Analog input channel 2 |
| `AIN3` | 0x03 | Analog input channel 3 |
| `ADC_SINGLE_CHANNEL` | 0x00 | Single-ended input mode |
| `ADC_DIFFERENTIAL` | 0x10 | Differential input mode |
| `ADC_MIXED` | 0x20 | Mixed input mode |
| `ADC_TWO_DIFFERENTIAL` | 0x30 | Two differential inputs mode |

---

## 📌 **Functions**
| Function | Description |
|----------|-------------|
| `void PCF8591_Init(void);` | Initializes the PCF8591 module |
| `void PCF8591_WriteDAC(u8 value);` | Writes a value to the DAC output |
| `u8 PCF8591_ReadADC(u8 channel);` | Reads from specified ADC channel |
| `u8 PCF8591_ReadDifference30(void);` | Reads differential input AIN3 - AIN0 |
| `u8 PCF8591_ReadDifference31(void);` | Reads differential input AIN3 - AIN1 |
| `u8 PCF8591_ReadDifference32(void);` | Reads differential input AIN3 - AIN2 |
| `u8 PCF8591_ReadDifference01(void);` | Reads differential input AIN0 - AIN1 |
| `u8 PCF8591_ReadDifference23(void);` | Reads differential input AIN2 - AIN3 |
| `void PCF8591_EnableDAC(void);` | Enables the DAC output |
| `void PCF8591_DisableDAC(void);` | Disables the DAC output |
| `void PCF8591_ChangeMode(u8 mode);` | Changes the ADC operation mode |

---

## 📌 **Usage Notes**
- Requires I2C library for communication
- Default I2C address is 0x90 (can be modified in header)
- Supports four analog input channels (AIN0-AIN3)
- Provides both single-ended and differential input modes
- Includes 8-bit DAC output functionality

---

## 📢 **Example Code**
The following example demonstrates how to read key presses from the 4x4 keypad:

```c
#include <8051.h> 
#include "../library/Delay/Delay.h"
#include "../library/PCF8591/PCF8591.h"
#include "../library/UART/UART.h"
#include <stdio.h>  

#define GAS_THRESHOLD 150

// Function to delay for approximately 1 second
void Delay1s() {
    unsigned int i;
    for (i = 0; i < 20000; i++) {
        DelayXus(5);  // Increased delay for better timing
    }
}

void main() {
    unsigned char adc_value;
    char str_value[4]; 
    
    UART_Init(9600);
    PCF8591_Init();
    UART_SendString("HI BUDDIES\n");
    
    while(1) {
        // Read from channel 0
        adc_value = PCF8591_ReadADC(AIN0);
        sprintf(str_value, "%u", adc_value);
        UART_SendString(str_value);
        UART_SendString("\n");
        
        // Simple LED control based on ADC value
        if(adc_value > GAS_THRESHOLD) {
            P1_1 = 1;  // Turn LED on
        } else {
            P1_1 = 0;  // Turn LED off
        }
        
        Delay1s();
    }
}
```

---

## 📢 **Important**
- Ensure proper I2C initialization before using PCF8591 functions
- Refer to PCF8591 datasheet for detailed specifications
- Default mode is single-channel ADC operation