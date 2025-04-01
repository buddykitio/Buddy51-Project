# EEPROM Library

This library provides functions to read from and write to an **I2C-based EEPROM (24LC16)** using an **8051 microcontroller** with **SDCC**.

---

## 📌 **Constants**
| Constant | Value | Description |
|----------|-------|-------------|
| `IC24LC16` | `0xA0` | EEPROM device address for 24LC16 |

---

## 📌 **Functions**
| Function | Description |
|----------|-------------|
| `u8 EEPROM_Goto(const u8 address, u8 mode);` | Sets the EEPROM's internal address pointer (used internally). |
| `u8 EEPROM_Write(u8 address, u8 data);` | Writes a single byte to a specified EEPROM address. |
| `u8 EEPROM_Read(u8 address, u8* data);` | Reads a single byte from a specified EEPROM address. |
| `u8 EEPROM_Writes(u8 address, void* vData, u8 length);` | Writes multiple bytes to EEPROM starting from the given address. |
| `u8 EEPROM_Reads(u8 address, void* vData, u8 length);` | Reads multiple bytes from EEPROM starting from the given address. |

---

## 📢 **Notes**
- This library uses the **I2C Library** for communication.
- Designed for **SDCC-based 8051 microcontrollers**.
- Modify the **I2C pin assignments** in the **I2C library** if required.
