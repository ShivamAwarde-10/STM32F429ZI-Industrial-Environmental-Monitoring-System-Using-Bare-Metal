#include "i2c.h"

/* RCC */

#define RCC_BASE        0x40023800UL

#define RCC_AHB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define RCC_APB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x40))

/* GPIOB */

#define GPIOB_BASE      0x40020400UL

#define GPIOB_MODER     (*(volatile uint32_t *)(GPIOB_BASE + 0x00))
#define GPIOB_OTYPER    (*(volatile uint32_t *)(GPIOB_BASE + 0x04))
#define GPIOB_OSPEEDR   (*(volatile uint32_t *)(GPIOB_BASE + 0x08))
#define GPIOB_PUPDR     (*(volatile uint32_t *)(GPIOB_BASE + 0x0C))
#define GPIOB_AFRH      (*(volatile uint32_t *)(GPIOB_BASE + 0x24))

/* I2C1 */

#define I2C1_BASE       0x40005400UL

#define I2C1_CR1        (*(volatile uint32_t *)(I2C1_BASE + 0x00))
#define I2C1_CR2        (*(volatile uint32_t *)(I2C1_BASE + 0x04))
#define I2C1_DR         (*(volatile uint32_t *)(I2C1_BASE + 0x10))
#define I2C1_SR1        (*(volatile uint32_t *)(I2C1_BASE + 0x14))
#define I2C1_SR2        (*(volatile uint32_t *)(I2C1_BASE + 0x18))
#define I2C1_CCR        (*(volatile uint32_t *)(I2C1_BASE + 0x1C))
#define I2C1_TRISE      (*(volatile uint32_t *)(I2C1_BASE + 0x20))

// I2C initialization function
void I2C_Init(void)
{
    RCC_AHB1ENR |= (1U << 1);              // Enable GPIOB peripheral clock

    RCC_APB1ENR |= (1U << 21);             // Enable I2C1 peripheral clock

    GPIOB_MODER &= ~(3U << 16);            // Clear mode bits of PB8

    GPIOB_MODER |=  (2U << 16);            // Configure PB8 as Alternate Function mode

    GPIOB_MODER &= ~(3U << 18);            // Clear mode bits of PB9

    GPIOB_MODER |=  (2U << 18);            // Configure PB9 as Alternate Function mode

    GPIOB_OTYPER |= (1U << 8);             // Configure PB8 as Open-Drain output

    GPIOB_OTYPER |= (1U << 9);             // Configure PB9 as Open-Drain output

    GPIOB_PUPDR &= ~(3U << 16);            // Clear pull-up/pull-down bits of PB8

    GPIOB_PUPDR |=  (1U << 16);            // Enable Pull-Up resistor on PB8

    GPIOB_PUPDR &= ~(3U << 18);            // Clear pull-up/pull-down bits of PB9

    GPIOB_PUPDR |=  (1U << 18);            // Enable Pull-Up resistor on PB9

    GPIOB_OSPEEDR |= (3U << 16);           // Configure PB8 for High-Speed operation

    GPIOB_OSPEEDR |= (3U << 18);           // Configure PB9 for High-Speed operation

    GPIOB_AFRH &= ~(0xFU << 0);            // Clear alternate function bits of PB8

    GPIOB_AFRH |=  (4U << 0);              // Select AF4 (I2C1_SCL) for PB8

    GPIOB_AFRH &= ~(0xFU << 4);            // Clear alternate function bits of PB9

    GPIOB_AFRH |=  (4U << 4);              // Select AF4 (I2C1_SDA) for PB9

    I2C1_CR2 = 16;                         // Configure APB1 clock frequency as 16 MHz

    I2C1_CCR = 80;                         // Configure I2C clock for Standard Mode (100 kHz)

    I2C1_TRISE = 17;                       // Configure maximum rise time

    I2C1_CR1 |= (1U << 0);                 // Enable I2C1 peripheral
}

// Generate I2C Start condition
void I2C_Start(void)
{
    I2C1_CR1 |= (1U << 8);                 // Generate START condition

    while(!(I2C1_SR1 & (1U << 0)));        // Wait until START condition is generated
}

// Generate I2C Stop condition
void I2C_Stop(void)
{
    I2C1_CR1 |= (1U << 9);                 // Generate STOP condition
}

// Send slave address on I2C bus
void I2C_SendAddress(uint8_t address)
{
    I2C1_DR = address;                     // Send 7-bit slave address with R/W bit

    while(!(I2C1_SR1 & (1U << 1)));        // Wait until address is acknowledged

    (void)I2C1_SR1;                        // Read SR1 to clear ADDR flag

    (void)I2C1_SR2;                        // Read SR2 to complete ADDR flag clearing
}

// Write one byte of data over I2C
void I2C_Write(uint8_t data)
{
    while(!(I2C1_SR1 & (1U << 7)));        // Wait until transmit data register is empty

    I2C1_DR = data;                        // Write data into data register

    while(!(I2C1_SR1 & (1U << 2)));        // Wait until byte transfer is finished
}

// Read one byte and send ACK
uint8_t I2C_Read_ACK(void)
{
    I2C1_CR1 |= (1U << 10);                // Enable ACK generation

    while(!(I2C1_SR1 & (1U << 6)));        // Wait until data is received

    return (uint8_t)I2C1_DR;               // Return received data byte
}

// Read one byte and send NACK
uint8_t I2C_Read_NACK(void)
{
    I2C1_CR1 &= ~(1U << 10);               // Disable ACK generation (send NACK)

    while(!(I2C1_SR1 & (1U << 6)));        // Wait until data is received

    return (uint8_t)I2C1_DR;               // Return received data byte
}

