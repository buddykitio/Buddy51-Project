#include "uart.h"
#include <8051.h>  // SDCC's 8051 header


// Initialize UART with specified baud rate
void UART_Init(u16 baudrate)
{
    // Standard baud rate values for 11.0592MHz crystal
    u8 th1_value;
    
    // Set Timer 1 mode 2 (8-bit auto-reload)
    TMOD &= 0x0F;   // Clear all T1 bits
    TMOD |= 0x20;   // Set T1 to mode 2
    
    // Set serial port mode 1 (8-bit UART, variable baud rate)
    SCON = 0x50;    // Mode 1, Receiver enabled
    
    // Calculate TH1 value based on baud rate
    switch(baudrate)
    {
        case 9600:
            th1_value = 0xFD;   // 9600 baud
            PCON &= 0x7F;       // SMOD = 0
            break;
            
        case 19200:
            th1_value = 0xFD;   // 19200 baud
            PCON |= 0x80;       // SMOD = 1
            break;
            
        case 57600:
            th1_value = 0xFF;   // 57600 baud
            PCON |= 0x80;       // SMOD = 1
            break;
            
        case 115200:
            th1_value = 0xFF;   // 115200 baud
            PCON |= 0x80;       // SMOD = 1
            break;
            
        default:    // Default to 9600
            th1_value = 0xFD;
            PCON &= 0x7F;
            break;
    }
    
    TH1 = TL1 = th1_value;     // Set timer value
    TR1 = 1;                   // Start timer 1
}

// Send a single character
void UART_SendChar(u8 ch)
{
    SBUF = ch;      // Load data into buffer
    while(TI == 0); // Wait for transmission complete
    TI = 0;         // Clear transmit interrupt flag
}

// Send a string
void UART_SendString(u8 *str)
{
    while(*str)
    {
        UART_SendChar(*str++);
    }
}

// Check if data is available
u8 UART_DataAvailable()
{
    return RI;  // Return receive interrupt flag status
}

// Receive a single character
u8 UART_ReceiveChar()
{
    while(RI == 0); // Wait for reception complete
    RI = 0;         // Clear receive interrupt flag
    return SBUF;    // Return received data
}

