# Servo Motor Control Library (Software PWM)

### Overview
This library provides software PWM control for hobby servo motors using **Timer 1** on the 8051 microcontroller. It calculates ON and OFF pulse durations based on the servo angle (0° to 180°) and generates the PWM signal accordingly.

### Function Summary
| Function                              | Return Type | Description                                            |
| ------------------------------------- | ----------- | ------------------------------------------------------ |
| `waitServoPulse(u16 angle, u8 isOff)` | `void`      | Generates ON or OFF pulse duration for the given angle |

### Macro Definitions
| Macro       | Value | Description                 |
| ----------- | ----- | --------------------------- |
| `SERVO_ON`  | 0     | Generate ON pulse duration  |
| `SERVO_OFF` | 1     | Generate OFF pulse duration |

Use these with `waitServoPulse()` to specify the pulse phase.

### How It Works
* Standard servo requires a PWM signal every **20 ms (50 Hz)**.
* ON time varies from:

  * \~0.5 ms (0°)
  * \~1.5 ms (90°)
  * \~2.5 ms (180°)
* OFF time is the remainder to complete 20 ms.
* Timer 1 is configured in 16-bit mode to measure pulse duration.
* Pulse width is calculated as:

```c
pulseWidth = 500 + (angle * 2000 / 180);
```

* OFF time calculated as:

```c
offDuration = 20000 - pulseWidth;
```

* Timer ticks for 8051 (12 MHz clock) are computed:

```c
ticks = 65536 - (pulseWidth * 59 / 64);
```

### Usage Example
```c
#include <8051.h>
#include "..\library\Motor\Motor.h"
#include "..\library\type.h"

#define DOOR_MOTOR_PIN P1_1

void main() {
    while (1) {
        DOOR_MOTOR_PIN = 1;
        waitServoPulse(90, SERVO_ON);  // ON pulse for 90°
        DOOR_MOTOR_PIN = 0;
        waitServoPulse(90, SERVO_OFF); // OFF pulse to complete 20 ms
    }
}
```

---
### Dependencies

* Timer utilities or delay functions for pulse timing.
* `type.h` defining `u16` (16-bit unsigned integer).

---

### Notes

* Servo should have a separate power source if required.
* This is a **blocking software PWM**, CPU is halted during delay.
* Total ON + OFF pulse duration must be about 20 ms.
* Use hardware PWM if multitasking is needed.

---

### Troubleshooting

| Problem             | Possible Cause                        |
| ------------------- | ------------------------------------- |
| Servo jitters/stuck | Timer conflicts or busy-wait issues   |
| Servo not moving    | Wiring mistakes or wrong pulse timing |
| Random movement     | Power noise or insufficient delays    |
