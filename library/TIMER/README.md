# Timer Library for 8051

This library provides timer functions for 8051 microcontrollers using SDCC compiler.

---

## 📌 **Features**
- Support for Timer 0 and Timer 1
- 16-bit timer mode (Mode 1)
- Automatic reload calculation
- Interrupt-driven operation
- Millisecond timing support

---

## 📌 **Macros**

| Macro | Value | Description |
|-------|-------|-------------|
| `TIMER0` | 0 | Timer 0 selection |
| `TIMER1` | 1 | Timer 1 selection |

---

## 📌 **Functions**

| Function | Description |
|----------|-------------|
| `void timer_init(u8 timer)` | Initializes specified timer in 16-bit mode |
| `void timer_start(u8 timer, uint reload_val)` | Starts timer with specified reload value |
| `uint timer_calc(unsigned long ms, unsigned long freq)` | Calculates reload value for given milliseconds and frequency |

---

## 📌 **Interrupt Service Routines**
| ISR | Description |
|-----|-------------|
| `timer0_isr()` | Timer 0 interrupt handler |
| `timer1_isr()` | Timer 1 interrupt handler |

---

## 📌 **Global Variables**
| Variable | Description |
|----------|-------------|
| `timer0_ticks` | Counter for Timer 0 interrupts |
| `timer1_ticks` | Counter for Timer 1 interrupts |

---

## 📌 **Usage Example**

```c
#include <8051.h>
#include "timer.h"

#define LED P1_1

void main() {
    // Initialize and start timer (50ms @ 11.0592MHz)
    timer_init(TIMER1);
    unsigned int reload = timer_calc(50, 11059200);
    timer_start(TIMER1, reload);
    
    while(1) {
        if(timer1_ticks >= 20) {  // 20*50ms = 1 second
            LED = !LED;
            timer1_ticks = 0;
        }
    }
}
```

---

## 📌 **Configuration Notes**
- Default crystal frequency: 11.0592MHz
- Timer mode: 16-bit (Mode 1)
- Automatic reload in ISR for periodic operation
- Requires `system.h` and `type.h` for type definitions

---

## 📢 **Important Notes**
- Ensure proper interrupt priorities if using multiple interrupts
- Timer calculations assume 12-clock mode (standard 8051)
- Clear timer flags in ISR when using different modes
- Global interrupts must be enabled (EA = 1)