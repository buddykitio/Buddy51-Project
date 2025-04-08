#ifndef _DS1307_H_
#define _DS1307_H_

#include "../system.h"
#include <8052.h>
#include "../type.h"
#include "../I2C/I2C.h"
#include "../Delay/Delay.h"

#define DS1307 0xD0
#define RAM_OFFSET 0x08

#define IS_LEAP_YEAR(y) (((y) % 4 == 0 && (y) % 100 != 0) || (y) % 400 == 0)

extern u8 seconds, minutes, hours, date, month, year, dayOfWeek;

static void RTC_Init(void);
static u8 RTC_Read(void);
static void RTC_Write(void);
static void RTC_Time2Str(u8* str);
static void RTC_Date2Str(u8* str);
static u16 getDayOfYear(void);
static void RTC_WriteData(u8 addr, u8 dat);
static u8 RTC_ReadData(u8 addr);

#endif