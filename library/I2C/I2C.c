#include "I2C.h"

// Initialize I2C communication (sets SDA and SCL to idle high)
void I2C_Init(void){
	SDA = 1;  // Set SDA to high (idle)
	SCL = 1;  // Set SCL to high (idle)
}

// Start I2C communication (SDA transitions from high to low while SCL is high)
void I2C_Start(void){
	SDA = 1; _nop_();  // Ensure SDA is high
	SCL = 1; _nop_();  // Ensure SCL is high
	SDA = 0; _nop_();  // Start condition: SDA goes low
	SCL = 0;            // Keep SCL low
}

// Stop I2C communication (SDA transitions from low to high while SCL is high)
void I2C_Stop(void){
	SDA = 0; _nop_();   // Ensure SDA is low
	SCL = 1; _nop_();   // Set SCL high
	SDA = 1;            // Stop condition: SDA goes high
}

// Write data to I2C (8-bit data sent MSB first)
u8 I2C_Write(const u8 dat){
	u8 mask = 0x80;    // Start with the MSB (bit 7)
	
	// Loop through each bit of the data byte (MSB to LSB)
	while(mask){
		// Write the bit to SDA (set SDA based on the corresponding data bit)
		if(dat & mask)
			SDA = 1;  // Set SDA to 1 if bit is 1
		else
			SDA = 0;  // Set SDA to 0 if bit is 0

		SCL = 1; _nop_();  // Clock pulse: Set SCL high
		SCL = 0;            // Clock pulse: Set SCL low
		mask >>= 1;         // Shift to the next bit (move to next bit of 'dat')
  }
	
	SDA = 1;  // Release SDA line (prepare for ACK/NACK)
	SCL = 1;   // Send clock pulse to receive ACK/NACK
	mask = SDA; // Read ACK/NACK response on SDA line
	SCL = 0;   // Clock low after receiving ACK/NACK

	return mask;  // Return ACK/NACK value (1 for ACK, 0 for NACK)
}

// Read data from I2C (8-bit data received, ACK sent after each byte)
u8 I2C_Read(u8 ack){
	u8 i, dat = 0;

	SDA = 1;  // Prepare SDA to receive data (release it for input)
	// Loop through 8 clock cycles to receive 8 bits
	for(i = 0; i < 8; i++){
		dat <<= 1;  // Shift received bits to the left
		SCL = 1; _nop_();  // Set clock high for data bit transfer
		if(SDA)    // Check if SDA is high (data bit is 1)
			dat++;  // If SDA is high, set the bit to 1
		SCL = 0;  // Set clock low after reading the bit
	}

	// Send ACK or NACK based on the ack parameter (1 = ACK, 0 = NACK)
	SDA = ack;
	SCL = 1; _nop_();  // Clock pulse to send ACK/NACK
	SCL = 0;            // Clock low to finish
	
	return dat;  // Return the 8-bit data read from I2C
}
