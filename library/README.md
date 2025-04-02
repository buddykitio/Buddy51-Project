# System and Type Library for 8051

1. **system.h** – Defines system clock settings and delay configurations.  
2. **type.h** – Provides standard data types, macros, and bitwise definitions.

---

## 📌 **System Library (system.h)**
This file defines **CPU clock frequency** and delay timer settings.

### **Constants**
| Constant | Value | Description |
|----------|-------|-------------|
| `CPU_CLK` | `11059200UL` | System clock frequency (11.0592 MHz) |
| `MACHINE_CYCLE` | `(CPU_CLK / 12)` | Machine cycle frequency |
| `DELAY_TIMER` | `1` | Defines the which timer used for 1ms delay |

### **Usage**
- The `CPU_CLK` value must match the actual **crystal oscillator** used in the system.
- The `DELAY_TIMER` setting determines which timer is used for **1ms delay**.

---

## 📌 **Type Library (type.h)**
This file provides **standard data types**, **bitwise macros**, and **helper functions**.

### **Data Type Definitions**
| Type | Description |
|------|-------------|
| `u8`, `uint8_t`, `BYTE` | 8-bit unsigned integer |
| `u16`, `uint16_t`, `WORD` | 16-bit unsigned integer |
| `u32`, `uint32_t`, `LWORD` | 32-bit unsigned integer |
| `s8`, `int8_t` | 8-bit signed integer |
| `s16`, `int16_t` | 16-bit signed integer |
| `s32`, `int32_t` | 32-bit signed integer |

### **Boolean and Bit Definitions**
| Macro | Value | Description |
|--------|-------|-------------|
| `SET` | `1` | Used to set a bit |
| `CLR` | `0` | Used to clear a bit |
| `TRUE` | `1` | Boolean true |
| `FALSE` | `0` | Boolean false |
| `YES` | `1` | Alternative for `TRUE` |
| `NO` | `0` | Alternative for `FALSE` |

### **Bit Manipulation Macros**
| Macro | Description |
|--------|-------------|
| `HIBYTE(V1)` | Extracts high byte from a 16-bit value |
| `LOBYTE(V1)` | Extracts low byte from a 16-bit value |

### **NOP Instruction**
A **No Operation (NOP)** instruction is included for **precise timing** control.
```c
#define NOP() __asm nop __endasm
#define _nop_ NOP
```