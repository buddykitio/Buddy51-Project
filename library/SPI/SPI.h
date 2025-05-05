#ifndef __SPI_H__
#define __SPI_H__

#include <8052.h>          // 8051 microcontroller header
#include "../type.h"       // Custom type definitions (likely contains u8, u16 etc.)
#include "../Delay/Delay.h"// Delay function declarations

#define MOSI  P3_7  // Master Out Slave In
#define MISO  P3_6  // Master In Slave Out
#define SCK   P3_5  // Serial Clock

 void SPI_Init();
 void SPI_Write(u8 data);
 u8 SPI_Read();

#endif