#include "uart.h"

// Initialize UART with specified baud rate using Timer 2
void UART_Init(u16 baudrate)
{
    u16 reload;

    SCON = 0x50;  // Serial mode 1, REN enabled

    // Calculate reload value for Timer 2 (baud = Freq / (32 * (65536 - RCAP2)))
    switch (baudrate)
    {
        case 9600:
            reload = 65536 - (CPU_CLK / (32UL * 9600));
            break;
        case 19200:
            reload = 65536 - (CPU_CLK / (32UL * 19200));
            break;
        case 57600:
            reload = 65536 - (CPU_CLK / (32UL * 57600));
            break;
        case 115200:
            reload = 65536 - (CPU_CLK / (32UL * 115200));
            break;
        default:
            reload = 65536 - (CPU_CLK / (32UL * 9600));
            break;
    }

    // Load reload value into RCAP2 registers
    RCAP2H = (u8)(reload >> 8);
    RCAP2L = (u8)(reload & 0xFF);

    // Also initialize TH2 and TL2 for immediate effect
    TH2 = RCAP2H;
    TL2 = RCAP2L;

    // Configure Timer 2: auto-reload mode, baud rate generator
    T2CON = 0x34;  // TCLK=1, RCLK=1, TR2=1 (start timer)

    // No interrupts used here, disable for now
    ES = 0;
}

// Send a single character
void UART_SendChar(u8 ch)
{
    SBUF = ch;
    while (TI == 0);
    TI = 0;
}

// Send a null-terminated string
void UART_SendString(u8 *str)
{
    while (*str)
    {
        UART_SendChar(*str++);
    }
}

// Check if data is available
u8 UART_DataAvailable(void)
{
    return RI;
}

// Receive a single character
u8 UART_ReceiveChar(void)
{
    while (RI == 0);
    RI = 0;
    return SBUF;
}
