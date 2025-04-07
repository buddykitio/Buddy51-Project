#include "MPU6050.h"
#include "../I2C/I2C.h"

s16 AccX, AccY, AccZ;
s16 GyroX, GyroY, GyroZ;

void MPU6050_Init(void)
{
    I2C_Init();
    I2C_Start();
    I2C_Write(MPU_ADDR);
    I2C_Write(0x1C);
    I2C_Write(0x10);
    I2C_Stop();
    
    I2C_Start();
    I2C_Write(MPU_ADDR);
    I2C_Write(0x1B);
    I2C_Write(0x10);
    I2C_Stop();
}

void MPU6050_ReadAll(void)
{
    u8 data[14];

    I2C_Start();
    I2C_Write(MPU_ADDR);       // Write address
    I2C_Write(0x3B);           // Start from ACCEL_XOUT_H
    I2C_Start();
    I2C_Write(MPU_ADDR | 0x01); // Read address

    // Read 13 bytes with ACK, 14th with NACK
    for (u8 i = 0; i < 13; i++)
        data[i] = I2C_Read(0); // ACK
    data[13] = I2C_Read(1);    // NACK
    I2C_Stop();

    // Convert to signed 16-bit values
    AccX = ((s16)data[0] << 8) | data[1];
    AccY = ((s16)data[2] << 8) | data[3];
    AccZ = ((s16)data[4] << 8) | data[5];
    
    GyroX = ((s16)data[8] << 8) | data[9];
    GyroY = ((s16)data[10] << 8) | data[11];
    GyroZ = ((s16)data[12] << 8) | data[13];

    // Optional: Apply calibration offsets
    GyroX += 72;
    GyroY -= 262;
    GyroZ += 103;
}
