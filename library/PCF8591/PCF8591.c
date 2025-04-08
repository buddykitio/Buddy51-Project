#include "pcf8591.h"

static u8 _adc_mode = 0x00;

static void PCF8591_Init(void) {
    I2C_Init();
    PCF8591_ChangeMode(ADC_SINGLE_CHANNEL);
}

static void PCF8591_ChangeMode(u8 mode) {
    _adc_mode = mode & 0x30;  // Only keep mode bits (4-5)
}

static u8 PCF8591_ReadADC(u8 channel) {
    u8 value;
    
    if(channel > 3) channel = 0; // Default to channel 0 if invalid
    
    I2C_Start();
    I2C_Write(PCF8591_ADDR); // Device address + write
    I2C_Write(_adc_mode | channel); // Control byte with current mode and channel
    
    I2C_Start();
    I2C_Write(PCF8591_ADDR | 0x01); // Device address + read
    
    value = I2C_Read(0); // Read with NACK
    I2C_Stop();
    
    return value;
}

static void PCF8591_WriteDAC(u8 value) {
    I2C_Start();
    I2C_Write(PCF8591_ADDR); // Device address + write
    I2C_Write(0x40 | _adc_mode); // Enable DAC (bit 6) + current mode
    I2C_Write(value); // DAC value
    I2C_Stop();
}

static u8 PCF8591_ReadDifference30(void) {
    PCF8591_ChangeMode(ADC_DIFFERENTIAL);
    return PCF8591_ReadADC(AIN0); // AIN3 - AIN0
}

static u8 PCF8591_ReadDifference31(void) {
    if(!(_adc_mode & ADC_DIFFERENTIAL))
        PCF8591_ChangeMode(ADC_DIFFERENTIAL);
    return PCF8591_ReadADC(AIN1); // AIN3 - AIN1
}

static u8 PCF8591_ReadDifference32(void) {
    if(!(_adc_mode & ADC_DIFFERENTIAL))
        PCF8591_ChangeMode(ADC_DIFFERENTIAL);
    return PCF8591_ReadADC(AIN2); // AIN3 - AIN2
}

static u8 PCF8591_ReadDifference01(void) {
    if(!(_adc_mode & ADC_DIFFERENTIAL))
        PCF8591_ChangeMode(ADC_TWO_DIFFERENTIAL);
    return PCF8591_ReadADC(AIN0); // AIN0 - AIN1
}

static u8 PCF8591_ReadDifference23(void) {
    if(!(_adc_mode & ADC_MIXED) || !(_adc_mode & ADC_TWO_DIFFERENTIAL))
        PCF8591_ChangeMode(ADC_MIXED);
    return PCF8591_ReadADC(AIN2); // AIN2 - AIN3
}

static void PCF8591_EnableDAC(void) {
    _adc_mode  |= 0x40;
}

static void PCF8591_DisableDAC(void) {
   _adc_mode  &= ~0x40;
}

static u8 PCF8591_IsDACEnabled(void) {
    return ( _adc_mode  & 0x40) ? 1 : 0;
}
