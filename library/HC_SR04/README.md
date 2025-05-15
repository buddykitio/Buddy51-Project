# HC-SR04 Ultrasonic Distance Sensor Library

## 📌 Pin Connections

Modify these connections according to your hardware setup. The default pin mapping used in the library is:

| HC-SR04 Pin | 8051 Pin | Description             |
|-------------|----------|-------------------------|
| VCC         | +5V      | Power Supply            |
| GND         | GND      | Ground                  |
| TRIG        | P1.1     | Trigger signal output   |
| ECHO        | P1.0     | Echo signal input       |

> 📎 **Note:** You can change `#define TRIG` and `#define ECHO` in `HC_SR04.h` to match your hardware connections.

---

## 📌 Function in `HC_SR04.h`

| Function Name        | Return Type | Description                             |
|----------------------|-------------|-----------------------------------------|
| `getDistance(void)`  | `int`       | Returns distance in centimeters. If there's a timeout, returns `-1`. |

---

## 📌 How It Works

1. Sends a 10µs pulse through the **TRIG** pin.
2. Starts a timer and waits for **ECHO** to go high.
3. When **ECHO** is high, measures the pulse duration.
4. Converts time to distance using the speed of sound:
   - Formula: `Distance (cm) = (time in µs) × 0.034 / 2`
5. Applies a cap at 400 cm to filter out invalid values.

> ⚠️ This function uses **Timer 1** of the 8051 in 16-bit mode. Make sure Timer 1 is not used elsewhere in your application when calling this function.

---

## 📌 Dependencies

This library depends on the following modules:

- **[Delay Library](../Delay/README.md)** — for generating microsecond delay for the trigger pulse and loop timing.

---

## 📌 Usage Example

### Example: Read distance and send via UART

```c
#include <8052.h> 
#include "../library/Delay/Delay.h"
#include "../library/UART/UART.h"
#include "../library/HC_SR04/HC_SR04.h"
#include <stdio.h>  

void main() {
    int distance;
    char buffer[20];

    UART_Init(9600);
    UART_SendString("HI BUDDIES\n");

    while (1) {
        distance = getDistance();

        sprintf(buffer, "Distance: %ucm\n", distance);
        UART_SendString((unsigned char *)buffer);
        DelayXms(5);
    }
}
```

## 📌 Troubleshooting
| Problem                        | Possible Cause                             |
|--------------------------------|--------------------------------------------|
| Always returns -1              | ECHO pin not receiving signal or miswired  |
| Very inaccurate or zero values | Sensor not facing reflective object        |
| Random spikes in distance      | Electrical noise or timing issues          |
