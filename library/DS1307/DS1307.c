#include "DS1307.h"

#define IS_LEAP_YEAR(y) (((y) % 4 == 0 && (y) % 100 != 0) || (y) % 400 == 0)

 u8 seconds, minutes, hours, date = 1, month = 1, year, dayOfWeek;

 u8 BCD2HEX(u8 tmp) {
  return (((tmp & 0xF0) >> 4) * 10 + (tmp & 0x0F));
}

 u8 HEX2BCD(u8 tmp) {
  return (((tmp / 10) << 4) | (tmp % 10));
}

 void RTC_Init(void) {
  I2C_Init(); // Initialize the I2c module.
  I2C_Start(); // Start I2C communication

  I2C_Write(DS1307); // Connect to DS1307 by sending its ID on I2c Bus
  I2C_Write(0x07); // Select the Ds1307 ControlRegister to configure Ds1307

  I2C_Write(0x00); // Write 0x00 to Control register to disable SQW-Out

  I2C_Stop(); // Stop I2C communication after initializing DS1307
}

 u8 RTC_Read(void) {
  I2C_Start();
  if (I2C_Write(DS1307)) {
    I2C_Stop();
    return 1;
  };
	
	I2C_Write(0x00);
	I2C_Start();
	I2C_Write((u8)(DS1307 + 1)); //read
	
	seconds = BCD2HEX(I2C_Read(0)) & 0x3F;
	minutes = BCD2HEX(I2C_Read(0));
	hours = BCD2HEX(I2C_Read(0));
	dayOfWeek = BCD2HEX(I2C_Read(0));
	date = BCD2HEX(I2C_Read(0));
	month = BCD2HEX(I2C_Read(0));
	year = BCD2HEX(I2C_Read(1)) - 30;
	I2C_Stop();
	
	return 0;
}

 void RTC_Write(void){
  I2C_Start();
  I2C_Write((u8)(DS1307));
  I2C_Write(0x00);
  I2C_Write(HEX2BCD(seconds) & 0x3F);
  I2C_Write(HEX2BCD(minutes));
  I2C_Write(HEX2BCD(hours));
	I2C_Write(HEX2BCD(dayOfWeek));
	I2C_Write(HEX2BCD(date));
	I2C_Write(HEX2BCD(month));
	I2C_Write(HEX2BCD(year + 30));
  I2C_Stop();
}

 void RTC_Time2Str(u8* str) {
  u8 hr;

  hr = hours % 12;
  if (hr == 0)
    hr = 12;

  str[0] = '0' + (hr / 10);
  str[1] = '0' + (hr % 10);
  str[2] = ':';
  str[3] = '0' + (minutes / 10);
  str[4] = '0' + (minutes % 10);
  str[5] = ':';
  str[6] = '0' + (seconds / 10);
  str[7] = '0' + (seconds % 10);

  str[8] = hours >= 12 ? 'P' : 'A';
  str[9] = 'M';

  str[10] = 0;
}

 void RTC_Date2Str(u8* str) {
  char* daysOfWeek[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

  str[0] = '0' + (date / 10);
  str[1] = '0' + (date % 10);
  str[2] = '/';
  str[3] = '0' + (month / 10);
  str[4] = '0' + (month % 10);
  str[5] = '/';
  str[6] = '0' + (year / 10);
  str[7] = '0' + (year % 10);
  str[8] = ' ';
	str[9] = daysOfWeek[dayOfWeek][0];
	str[10] = daysOfWeek[dayOfWeek][1];
	str[11] = daysOfWeek[dayOfWeek][2];

  str[12] = 0;
}

 u16 getDayOfYear(void) {
code u8 daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
u16 totalDays = 0;
u8 i;

	if (IS_LEAP_YEAR(year)) {
		daysInMonth[2] = 29;
	}
	
	for (i = 1; i < month; ++i) {
		totalDays += daysInMonth[i];
	}
	totalDays += date;
	
	return totalDays;
}

 void RTC_WriteData(u8 addr, u8 dat) {
  I2C_Start();
  I2C_Write(DS1307);
  I2C_Write(addr + RAM_OFFSET);
  I2C_Write(dat);
  I2C_Stop();
}

 u8 RTC_ReadData(u8 addr) {
u8 dat;
	
  I2C_Start();
  if (I2C_Write(DS1307)) {
    I2C_Stop();
    return 1;
  };
	
	I2C_Write(addr + RAM_OFFSET);
	I2C_Start();
	I2C_Write(DS1307 + 1); //read
	dat = I2C_Read(1);
	I2C_Stop();
	
	return dat;
}
