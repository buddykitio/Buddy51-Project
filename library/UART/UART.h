#ifndef _UART_H_
#define _UART_H_

#include <8052.h>
#include "../type.h"
#include "../system.h"

// Initialize UART with specified baud rate
void UART_Init(u16 baudrate);
// Send a single character
void UART_SendChar(u8 ch);
// Send a string
void UART_SendString(u8 *str);
// Check if data is available
u8 UART_DataAvailable();
// Receive a single character
u8 UART_ReceiveChar();

#endif