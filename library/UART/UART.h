#ifndef _UART_H_
#define _UART_H_

#include <8052.h>
#include "../type.h"
#include "../system.h"

// Initialize UART with specified baud rate
static void UART_Init(u16 baudrate);
// Send a single character
static void UART_SendChar(u8 ch);
// Send a string
static void UART_SendString(u8 *str);
// Check if data is available
static u8 UART_DataAvailable(void);
// Receive a single character
static u8 UART_ReceiveChar(void);

#endif