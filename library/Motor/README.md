# Servo Motor Control Library (Software PWM)

## 📌 Overview

This library allows you to control a servo motor using software-based PWM pulses via GPIO pins on an 8051 microcontroller.

It generates ON and OFF pulse durations based on the desired angle (0–180°), suitable for standard hobby servo motors.

---

## 📌 Function Summary

| Function Name            | Return Type | Description                                             |
|--------------------------|-------------|---------------------------------------------------------|
| `waitServoOnPulse(u16 angle)`  | `void`      | Generates a HIGH pulse (ON time) for the given angle     |
| `waitServoOffPulse(u16 angle)` | `void`      | Generates a LOW pulse (OFF time) to complete the PWM cycle |

> 🔧 These functions must be called in succession inside a loop to continuously generate PWM signals.

---

## 📌 How It Works

- **PWM Basics for Servo:**
  - A standard servo expects a pulse every 20 ms (50 Hz).
  - The ON time (HIGH signal) determines the angle:
    - ~0.5 ms for 0°
    - ~1.5 ms for 90°
    - ~2.5 ms for 180°
  - The OFF time fills the rest of the 20 ms period.

- **Example PWM Timing:**
  - For 90°:
    - `waitServoOnPulse(90)` → 1.5 ms ON
    - `waitServoOffPulse(90)` → 18.5 ms OFF

---

## 📌 Usage Example

```c
#include <8051.h>
#include "..\library\Motor\Motor.h"
#include "..\library\type.h"

#define DOOR_MOTOR_PIN P1_1

void main() {
    // Configure Timer 0: Mode 1 (16-bit)
    TMOD &= 0xF0;   // Clear lower 4 bits for Timer 0
    TMOD |= 0x01;   // Set Mode 1 (16-bit)

    while (1) {
        DOOR_MOTOR_PIN = 1;
        waitServoOnPulse(90);   // Send pulse for 90-degree position
        DOOR_MOTOR_PIN = 0;
        waitServoOffPulse(90);  // Wait remaining time for PWM period
    }
}
```

### 📌 Dependencies
This library depends on the following modules:
- Delay or Timer Utilities — used internally for pulse timing.
- type.h — defines u16 (16-bit unsigned integer type).

### 📌 Notes
- Make sure the servo is powered separately if it draws significant current.
- This method uses software PWM, which blocks the CPU during the pulse. Use hardware PWM if CPU multitasking is needed.
- Ensure that waitServoOnPulse() + waitServoOffPulse() total approximately 20 ms for stable servo operation.