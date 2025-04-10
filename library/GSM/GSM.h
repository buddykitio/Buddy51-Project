#ifndef __GSM_H__
#define __GSM_H__



#include "../UART/UART.h"
#include <8051.h>  // SDCC's 8051 header

#define GSM_READY_TIMEOUT 50000
#define GSM_OK_TIMEOUT 30000
#define GSM_RESPONSE_OK "OK"
#define GSM_RESPONSE_ERROR "ERROR"

u8 GSM_IsReady(void);
u8 UART_WaitForResponse(u16 timeout);
u8 CompareResponse(const char *response);
void GSM_SendSMS(const char *phoneNumber, const char *message);
void GSM_MakeCall(const char *phoneNumber);
void GSM_HangUp(void);
void GSM_GetSignalStrength(void);


#endif