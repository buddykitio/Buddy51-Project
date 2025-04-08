#ifndef _I2C_H_
#define _I2C_H_

#include "../system.h"
#include <8052.h>
#include "../type.h"

static void I2C_Init(void);
static void I2C_Start(void);
static void I2C_Stop(void);
static u8 I2C_Write(const u8 dat);
static u8 I2C_Read(u8 ack);

/* Pin Definitions - Modify these based on your hardware connections */
#define SDA P2_0       // SDA pin
#define SCL P2_1       // SCL pin (clock signal)

#endif