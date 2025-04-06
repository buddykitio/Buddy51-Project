# 6-Digit 7-Segment Display Library

This library provides functions to control a 6-digit 7-segment display (both Common Cathode (CC) and Common Anode (CA)) on 8051 microcontrollers using SDCC.

---

## 📌 **Functions**
| Function | Description |
|----------|-------------|
| `void SEG_Init(void);` | Initializes the 7-segment display. |
| `void SEG_Loop(void);` | Handles the continuous display refresh. |
| `void SEG_OutData(const char *datas);` | Displays numerical or character data on the 7-segment display. |

---

## 📌 **Pin Assignments**
By default, the 7-segment display library uses the following pin connections:

| Signal | 8051 Pin | Description |
|--------|---------|-------------|
| SEG_MODE | CC / CA | Selects Common Cathode or Common Anode mode. |
| SEG_PORT | P0 | Port used for segment data. |
| SEG1    | P2_0    | First digit enable pin. |
| SEG2    | P2_1    | Second digit enable pin. |
| SEG3    | P2_2    | Third digit enable pin. |
| SEG4    | P2_3    | Fourth digit enable pin. |
| SEG5    | P2_4    | Fifth digit enable pin. |
| SEG6    | P2_5    | Sixth digit enable pin. |
| DISPLAY_TIMER | 0 | Timer used for display refresh. |

If needed, you can modify these pin assignments in `LED_7SEGMENT.h`.

---

## 📢 **Example Code**
The following example demonstrates how to display numbers on a 6-digit 7-segment display:

```c
#include <8052.h> 
#include "../library/Delay/Delay.h"
#include "../library/LED_7SEGMENT/LED_7SEGMENT.h"

// Function to delay for approximately 1 second
void Delay1s() {
    unsigned int i;
    for (i = 0; i < 20000; i++) {
        DelayXus(5);
    }
}

DISPLAY_INTERRUPT()  // ❗❗ MUST BE INCLUDED FOR PROPER OPERATION ❗❗

void main() {
    SEG_Init();
    while(1) {
        SEG_OutData("1234.5");
        Delay1s();
        SEG_OutData("-67.890");
        Delay1s();
    } 
}
```

---

## 📣 **Important Notes**
- **❗ `DISPLAY_INTERRUPT()` must be included in your code, or the display will not function correctly.**
- This library is designed for SDCC-based 8051 microcontrollers.
- Modify pin assignments if required based on your hardware setup.
- Refer to the source code for detailed implementation.

