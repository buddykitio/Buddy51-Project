# UART Library

This library provides essential functions for serial communication via UART on 8051 microcontrollers.

---

## 📌 **Functions**

| Function | Description |
|----------|-------------|
| `void UART_Init(u16 baudrate);` | Initializes UART with specified baud rate |
| `void UART_SendChar(u8 ch);` | Transmits a single character |
| `void UART_SendString(u8 *str);` | Transmits a null-terminated string |
| `u8 UART_DataAvailable();` | Checks if receive data is available (returns 1 if data available, 0 otherwise) |
| `u8 UART_ReceiveChar();` | Receives a single character |

---

## 📌 **Typical Usage Example**

```c
#include <8052.h>
#include "../library/UART/UART.h"
#include "../library/Delay/Delay.h"

#define LED P1_1

void main(void) {
u8 received;
    // Initialize UART at 9600 baud
    UART_Init(9600);
    
    // Send welcome message
    UART_SendString("UART Ready\r\n");
    
    while(1) {
        // Echo received characters
        if(UART_DataAvailable()) {
            received = UART_ReceiveChar();
            UART_SendChar(received);
        }
    }
}
```

---

## 📌 **Hardware Configuration**
By default, the library uses the following 8051 hardware resources:
- Timer 1 for baud rate generation
- UART mode 1 (8-bit data, 1 stop bit, no parity)
- P3.0 (RXD) for receive
- P3.1 (TXD) for transmit

---

## 📢 **Important Notes**
- Requires proper oscillator frequency configuration
- Baud rate accuracy depends on system clock frequency
- Ensure sufficient voltage levels for serial communication
- Functions are blocking (will wait until transmission completes)