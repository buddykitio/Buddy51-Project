# Delay Using Timer

## 📌 Overview
This library provides delay functions for the 8051 microcontroller using timers. It includes functions to generate microsecond using nop and millisecond delays uses Timer 0 or Timer 1, by default TIMER1

---

## 📌 Functions

| Function | Description |
|----------|-------------|
| `DelayXus(u8 xUs)` | Generates a short delay in microseconds. |
| `DelayXms(u16 xMs)` | Generates a delay in milliseconds using Timer|

---

## 📌 Usage Example

```c
#include <8052.h>
#include "Delay.h"

void main() {
    while (1) {
        P1 = 0xFF;  // Turn ON LEDs
        DelayXms(500); // 500ms delay
        P1 = 0x00;  // Turn OFF LEDs
        DelayXms(500); // 500ms delay
    }
}
```
**Explanation:**
- The example toggles the LEDs connected to Port 1 every 500 milliseconds.
- The `DelayXms()` function is used to create the delay.

---

## 📌 Constants and Macros

### Timer Reload Calculation
These macros compute the values required to load into the timer registers for accurate delay generation.

```c
#define TIMER_RELOAD (0xFFFF - _1MS_COUNT + 1)
#define THX ((TIMER_RELOAD >> 8) & 0xFF)  // High byte
#define TLX (TIMER_RELOAD & 0xFF)         // Low byte
```

- **TIMER_RELOAD**: Computes the 16-bit reload value for the timer.
- **THX**: Extracts the high byte of the reload value.
- **TLX**: Extracts the low byte of the reload value.

---

## 📢 Notes
- Ensure `_1MS_COUNT` is defined correctly according to the system clock frequency.
- Timer reload values must be adjusted if using different clock speeds.
- Using Timer 0 and Timer 1 for delays simultaneously may interfere with other timing operations.
