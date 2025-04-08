#include "SPI.h"

#define MOSI  P3_7  // Master Out Slave In
#define MISO  P3_6  // Master In Slave Out
#define SCK   P3_5  // Serial Clock

// SPI Initialization
static void SPI_Init() {
    MISO = 1;
    MOSI = 0;  // MOSI as output
    SCK = 0;   // Set clock low
}

// SPI Write (Master -> Slave)
static void SPI_Write(u8 data) {
    u8 mask = 0x80;

    while(mask) {
        MOSI = (data & mask) ? 1 : 0;  // Send MSB first
        mask >>= 1;                    // Shift data left
        nop();
        SCK = 1;                        // Clock high
        nop();
        SCK = 0;                        // Clock low
    }
}

// SPI Read (Slave -> Master)
static u8 SPI_Read() {
    u8 data = 0, mask = 0x80;
    
    while(mask){
        SCK = 1;            // Clock high
        nop();
        if (MISO) {         // Read MISO
            data |= mask;
        }
        SCK = 0;            // Clock low
        mask >>= 1;
    }
    
    return data;
}
