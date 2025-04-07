# MPU6050 Sensor Library

This library provides essential functions to interface the MPU6050 sensor (accelerometer + gyroscope) via I2C on 8051 microcontrollers using SDCC.

---

## 📌 **Functions**
| Function | Description |
|----------|-------------|
| `void MPU6050_Init(void);` | Initializes the MPU6050 sensor. |
| `void MPU6050_ReadAll(void);` | Reads accelerometer and gyroscope data and stores them in global variables. |

---

## 📊 **Sensor Data Variables**
After calling `MPU6050_ReadAll()`, the following global variables will contain the latest sensor readings:

```c
extern s16 AccX, AccY, AccZ;    // Accelerometer data
extern s16 GyroX, GyroY, GyroZ;  // Gyroscope data
```

These can be accessed directly for application use.

---

## ⚙️ **I2C Address**
The MPU6050's default I2C write address is defined as:
```c
#define MPU_ADDR 0xD0
```
You may change this value if your device uses a different configuration.

---

## 📢 **Example Code**
The following example demonstrates how to initialize the sensor, read data, and send it via UART:

```c
#include "../library/MPU6050/MPU6050.h"
#include "../library/UART/UART.h"
#include "../library/Delay/Delay.h"

void UART_SendInt16(s16 val) {
    char buf[7];
    u8 i = 0;
    if (val < 0) {
        UART_SendChar('-');
        val = -val;
    }
    do {
        buf[i++] = (val % 10) + '0';
        val /= 10;
    } while (val && i < 6);
    while (i--)
        UART_SendChar(buf[i]);
}

void SendSensorData(void) {
    UART_SendString("ACC: ");
    UART_SendInt16(AccX); UART_SendChar(' ');
    UART_SendInt16(AccY); UART_SendChar(' ');
    UART_SendInt16(AccZ); UART_SendString("\r\n");

    UART_SendString("GYRO: ");
    UART_SendInt16(GyroX); UART_SendChar(' ');
    UART_SendInt16(GyroY); UART_SendChar(' ');
    UART_SendInt16(GyroZ); UART_SendString("\r\n");

    UART_SendString("------------------------\r\n");
}

void main(void) {
    UART_Init(9600);
    DelayXms(100);
    MPU6050_Init();

    while (1) {
        MPU6050_ReadAll();
        SendSensorData();
        DelayXms(2000);
    }
}
```

---

## 📣 **Important Notes**
- Make sure your I2C library is working correctly before using this sensor library.
- Sensor readings are stored in signed 16-bit integers (`s16`).
- This library is designed for SDCC-based 8051 microcontrollers.
- Refer to the source code for implementation details or to make custom changes.
