#ifndef _EEPROM_H_
#define _EEPROM_H_

#include "../type.h"
#include "../I2C/I2C.h"
#include "../system.h"
#include <8051.h>

// EEPROM I2C address for the 24LC16 EEPROM (fixed address)
#define IC24LC16 0xA0

u8 EEPROM_Goto(const u8 address, u8 mode);
u8 EEPROM_Write(u8 address, u8 data);
u8 EEPROM_Read(u8 address, u8* data);
u8 EEPROM_Writes(u8 address, void* vData, u8 length);
u8 EEPROM_Reads(u8 address, void* vData, u8 length);

#endif