#include "EEPROM.h"

// Navigate to a specified EEPROM address. 
// If mode is 0, it writes the address for writing.
// If mode is 1, it writes the address for reading.
static u8 EEPROM_Goto(const u8 address, u8 mode){
	I2C_Start();                // Start I2C communication
	if(I2C_Write(IC24LC16)){    // Write EEPROM address
		I2C_Stop();              // Stop I2C if write failed
		return 1;	
	}		
	I2C_Write((u8)address);   // Write the address to go to in EEPROM

	// If mode is 1 (read mode), issue a start condition and change the read address
	if(mode){
		I2C_Start();
		I2C_Write((u8)(IC24LC16 + 1)); // Send read command by adding 1 to IC24LC16 address
	}
	return 0;  // Return success
}

// Write a single byte to EEPROM
static u8 EEPROM_Write(u8 address, u8 value) {
    I2C_Start();                     // Start I2C communication
    if (I2C_Write(IC24LC16)) {        // Send EEPROM device address (write mode)
        I2C_Stop();
        return 1;
    }
    I2C_Write(address);               // Send memory address
    I2C_Write(value);                  // Send data byte
    I2C_Stop();                        // Stop communication
    DelayXms(10);                     // Wait for write cycle to complete
    return 0;
}

// Read a single byte from EEPROM
static u8 EEPROM_Read(u8 address, u8* value) {
    I2C_Start();                     // Start I2C communication
    if (I2C_Write(IC24LC16)) {        // Send EEPROM device address (write mode)
        I2C_Stop();
        return 1;
    }
    I2C_Write(address);               // Send memory address
    I2C_Start();                      // Restart communication for reading
    I2C_Write((u8)(IC24LC16 + 1));          // Send EEPROM device address (read mode)
    *value = I2C_Read(1);              // Read data with NACK (last byte)
    I2C_Stop();                       // Stop communication
    return 0;
}

// Write a block of data to EEPROM starting from the specified address
static u8 EEPROM_Writes(u8 address, void* vData, u8 length){
	u8* pData;
	u8 i;

	pData = (u8*) vData;  // Pointer to the data to write
	i = address;            // Starting address
	address += length;      // Ending address

	// Navigate to the starting address for writing
	if(EEPROM_Goto(i, 0)){
		I2C_Stop();  // Stop I2C if navigation fails
		return 1;	
	}		

	do{
		I2C_Write(*pData);  // Write the u8 of data
		DelayXus(200);      // Small delay for write completion
		pData++;            // Move to the next u8 of data
		i++;                // Move to the next address

		// If we've written 16 u8s, stop and restart for the next block
		if((i%16) == 0){
			I2C_Stop();        // Stop I2C
			DelayXms(10);   // Wait for EEPROM to finish writing
			if(EEPROM_Goto(i, 0)){
				I2C_Stop();    // Stop I2C if navigation fails
				return 1;	
			}
		}
	}while(i < address);  // Continue until the full data is written

	I2C_Stop();  // Stop I2C after writing all data
	DelayXms(10);  // Wait to ensure write is completed
	return 0;  // Return success
}

// Read a block of data from EEPROM starting from the specified address
static u8 EEPROM_Reads(u8 address, void* vData, u8 length){
	u8* pData;
	u8 i;

	pData = (u8*) vData;  // Pointer to store read data
	i = address;            // Starting address
	address += length;      // Ending address
	
	// Navigate to the starting address for reading
	if(EEPROM_Goto(i, 1)){
		I2C_Stop();  // Stop I2C if navigation fails
		return 1;	
	}		

	while(length){
		length--;           // Decrease the length of remaining data
		i++;                // Move to the next address

		// If we've read 16 u8s, stop and restart for the next block
		if((i%16) == 0){
			*pData = I2C_Read(1);  // Read a u8 of data with ACK
			I2C_Stop();            // Stop I2C
			DelayXms(10);       // Wait for EEPROM to finish reading
			if(EEPROM_Goto(i, 1)){
				I2C_Stop();        // Stop I2C if navigation fails
				return 1;	
			}
		}
		else{
			// Read remaining u8s, sending ACK for all but the last u8
			if(length)
				*pData = I2C_Read(0);  // Read u8 and send ACK
			else
				*pData = I2C_Read(1);  // Read last u8 and send NACK
		}
		pData++;  // Move to the next u8 in the data buffer
	}

	I2C_Stop();  // Stop I2C after reading all data
	return 0;    // Return success
}
