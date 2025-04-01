# I2C Library

This library provides essential functions to communicate using the I2C protocol on 8051 microcontrollers using SDCC.

---

## 📌 **Functions**
| Function | Description |
|----------|-------------|
| `void I2C_Init(void);` | Initializes the I2C bus. |
| `void I2C_Start(void);` | Sends a start condition. |
| `void I2C_Stop(void);` | Sends a stop condition. |
| `u8 I2C_Write(const u8 dat);` | Writes a byte to the I2C bus and returns acknowledgment status. |
| `u8 I2C_Read(u8 ack);` | Reads a byte from the I2C bus with acknowledgment control. |

---

## 📌 **Pin Assignments**
By default, the I2C library uses the following pin connections:

| Signal | 8051 Pin | Description |
|--------|---------|-------------|
| SDA    | P2_0    | Serial Data Line |
| SCL    | P2_1    | Serial Clock Line |

If needed, you can modify these pin assignments in the `I2C.h`.

---

## 📢 **Notes**
- This library is designed for SDCC-based 8051 microcontrollers.
- Modify pin assignments if required based on your hardware setup.
- Refer to the source code for detailed implementation.