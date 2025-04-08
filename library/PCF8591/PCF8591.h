#ifndef _PCF8591_H_
#define _PCF8591_H_

#include "../system.h"
#include <8052.h>
#include "../type.h"
#include "../I2C/I2C.h"
#include "../Delay/Delay.h"

// PCF8591 Address (0x90 for write, 0x91 for read)
#define PCF8591_ADDR 0x90

// Control byte options
#define AIN0       0x00
#define AIN1       0x01
#define AIN2       0x02
#define AIN3       0x03

#define ADC_SINGLE_CHANNEL      0x00
#define ADC_DIFFERENTIAL        0x10 
#define ADC_MIXED               0x20
#define ADC_TWO_DIFFERENTIAL    0x30


static void PCF8591_Init(void);
static void PCF8591_WriteDAC(u8 value);
static u8 PCF8591_ReadADC(u8 channel);

static u8 PCF8591_ReadDifference30(void);
static u8 PCF8591_ReadDifference31(void);
static u8 PCF8591_ReadDifference32(void);

static u8 PCF8591_ReadDifference01(void);
static u8 PCF8591_ReadDifference23(void);

static void PCF8591_EnableDAC(void);
static void PCF8591_DisableDAC(void);

static void PCF8591_ChangeMode(u8 mode);

#endif