#include "eeprom.h"
#include "i2c.h"

#define EEPROM_WRITE_ADDR    0xA0
#define EEPROM_READ_ADDR     0xA1

```c
// EEPROM write function
void EEPROM_Write(uint16_t address, uint8_t data)
{
    I2C_Start();                                   // Generate I2C Start condition

    I2C_SendAddress(EEPROM_WRITE_ADDR);            // Send EEPROM slave address with Write operation

    I2C_Write((address >> 8) & 0xFF);              // Send high byte of EEPROM memory address

    I2C_Write(address & 0xFF);                     // Send low byte of EEPROM memory address

    I2C_Write(data);                               // Write one byte of data into EEPROM

    I2C_Stop();                                    // Generate I2C Stop condition

    for(volatile uint32_t i = 0; i < 100000; i++); // Wait for EEPROM internal write cycle to complete
}

// EEPROM read function
uint8_t EEPROM_Read(uint16_t address)
{
    uint8_t data;                                  // Variable to store received EEPROM data

    I2C_Start();                                   // Generate I2C Start condition

    I2C_SendAddress(EEPROM_WRITE_ADDR);            // Send EEPROM slave address with Write operation

    I2C_Write((address >> 8) & 0xFF);              // Send high byte of EEPROM memory address

    I2C_Write(address & 0xFF);                     // Send low byte of EEPROM memory address

    I2C_Start();                                   // Generate Repeated Start condition

    I2C_SendAddress(EEPROM_READ_ADDR);             // Send EEPROM slave address with Read operation

    data = I2C_Read_NACK();                        // Read one byte of data and send NACK

    I2C_Stop();                                    // Generate I2C Stop condition

    return data;                                   // Return the received EEPROM data
}
```
