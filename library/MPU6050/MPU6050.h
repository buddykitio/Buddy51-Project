#ifndef __MPU6050_H__
#define __MPU6050_H__

#include "../system.h"
#include <8052.h>
#include "../type.h"
#include "../I2C/I2C.h"
#include "../Delay/Delay.h"

#define MPU_ADDR 0xD0  // MPU6050 I2C address (write address)

extern s16 AccX, AccY, AccZ;
extern s16 GyroX, GyroY, GyroZ;

static void MPU6050_Init(void);
static void MPU6050_ReadAll(void);

#endif