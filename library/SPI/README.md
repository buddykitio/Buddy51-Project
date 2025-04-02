# SPI Library

This library provides essential functions to communicate using the SPI protocol on 8051 microcontrollers using SDCC.

---

## 📌 **Functions**
| Function | Description |
|----------|-------------|
| `void SPI_Init(void);` | Initializes the SPI bus. |
| `void SPI_Write(u8 data);` | Writes a byte to the SPI bus. |
| `u8 SPI_Read(void);` | Reads a byte from the SPI bus. |

---

## 📌 **Pin Assignments**
By default, the SPI library uses the following pin connections:

| Signal | 8051 Pin | Description |
|--------|---------|-------------|
| MOSI   | P3_7    | Master Out Slave In |
| MISO   | P3_6    | Master In Slave Out |
| SCK    | P3_5    | Serial Clock |

If needed, you can modify these pin assignments in `SPI.h`.

---

## 📢 **Example Code**
The following example demonstrates SPI communication using the 74165 & 74595 shift registers:

```c
#include <8051.h> 
#include "../library/Delay/Delay.h"
#include "../library/SPI/SPI.h"

// Function to delay for approximately 1 second
void Delay1s() {
    unsigned int i;
    for (i = 0; i < 20000; i++) {
        DelayXus(5);
    }
}

#define LATCH  P3_4 //595 latch pin
#define LOAD   P3_3 //165 load/shift pin

// Example Usage
void main() {
    unsigned char received;
    
    SPI_Init();
    LOAD = 1;
    LATCH = 0;
    
    while (1){
        LOAD = 0;
        DelayXus(2);
        LOAD = 1;
        DelayXus(2);

        received = SPI_Read();  // Receive data
        SPI_Write(received);  // Send data
        LATCH = 1;
        DelayXus(1);
        LATCH = 0;
        DelayXus(1);

        Delay1s();
    }
}
```

---

## 📣 **Notes**
- This library is designed for SDCC-based 8051 microcontrollers.
- Modify pin assignments if required based on your hardware setup.
- Refer to the source code for detailed implementation.
