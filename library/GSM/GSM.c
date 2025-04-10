#include"GSM.h"

#define GSM_READY_TIMEOUT 50000
#define GSM_OK_TIMEOUT 30000
#define GSM_RESPONSE_OK "OK"
#define GSM_RESPONSE_ERROR "ERROR"

// Function to check if the SIM800L is ready
u8 GSM_IsReady()
{
    UART_SendString("AT\r\n");
    return UART_WaitForResponse(GSM_OK_TIMEOUT);
}

// Wait for a response from the GSM module (like "OK" or "ERROR")
u8 UART_WaitForResponse(u16 timeout)
{
    u16 counter = 0;
    while(counter < timeout)
    {
        if (UART_DataAvailable()) {
            u8 receivedChar = UART_ReceiveChar();
            if (receivedChar == '\r' || receivedChar == '\n') {
                // Check the response
                if (CompareResponse(GSM_RESPONSE_OK)) {
                    return 1;  // "OK" received
                }
                else if (CompareResponse(GSM_RESPONSE_ERROR)) {
                    return 0;  // "ERROR" received
                }
            }
        }
        counter++;
    }
    return 0;  // Timeout
}

// Compare the received response with a given string
u8 CompareResponse(const char *response)
{
    u8 i = 0;
    while(response[i] != '\0')
    {
        if (UART_DataAvailable()) {
            u8 receivedChar = UART_ReceiveChar();
            if (receivedChar != response[i]) {
                return 0;  // Mismatch
            }
        }
        i++;
    }
    return 1;  // Match
}

// Send a message using the SIM800L
void GSM_SendSMS(const char *phoneNumber, const char *message)
{
    UART_SendString("AT+CMGF=1\r\n");  // Set SMS mode to text
    if (UART_WaitForResponse(GSM_OK_TIMEOUT) == 0) {
        UART_SendString("ERROR: Failed to set SMS mode.\r\n");
        return;
    }
    
    UART_SendString("AT+CMGS=\"");
    UART_SendString(phoneNumber);  // Send phone number
    UART_SendString("\"\r\n");
    
    if (UART_WaitForResponse(GSM_OK_TIMEOUT) == 0) {
        UART_SendString("ERROR: Failed to send phone number.\r\n");
        return;
    }
    
    UART_SendString(message);  // Send message content
    UART_SendChar(26);  // Ctrl+Z to send SMS (end of message)
    
    if (UART_WaitForResponse(GSM_OK_TIMEOUT) == 0) {
        UART_SendString("ERROR: Failed to send SMS.\r\n");
        return;
    }
    UART_SendString("SMS sent successfully.\r\n");
}

// Make a call to a phone number
void GSM_MakeCall(const char *phoneNumber)
{
    UART_SendString("ATD");
    UART_SendString(phoneNumber);  // Dial the phone number
    UART_SendChar(';');
    UART_SendString("\r\n");
    
    if (UART_WaitForResponse(GSM_OK_TIMEOUT) == 0) {
        UART_SendString("ERROR: Failed to make call.\r\n");
    }
    else {
        UART_SendString("Call initiated successfully.\r\n");
    }
}

// Hang up the ongoing call
void GSM_HangUp()
{
    UART_SendString("ATH\r\n");
    if (UART_WaitForResponse(GSM_OK_TIMEOUT) == 0) {
        UART_SendString("ERROR: Failed to hang up.\r\n");
    }
    else {
        UART_SendString("Call hung up successfully.\r\n");
    }
}

// Get signal strength
void GSM_GetSignalStrength()
{
    UART_SendString("AT+CSQ\r\n");
    if (UART_WaitForResponse(GSM_OK_TIMEOUT) == 0) {
        UART_SendString("ERROR: Failed to get signal strength.\r\n");
    }
    else {
        UART_SendString("Signal strength retrieved.\r\n");
    }
}
