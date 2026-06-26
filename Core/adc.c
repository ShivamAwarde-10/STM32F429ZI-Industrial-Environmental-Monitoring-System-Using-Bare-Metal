#include "adc.h"

/* RCC */

#define RCC_BASE        0x40023800UL

#define RCC_AHB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define RCC_APB2ENR     (*(volatile uint32_t *)(RCC_BASE + 0x44))

/* GPIOA */

#define GPIOA_BASE      0x40020000UL

#define GPIOA_MODER     (*(volatile uint32_t *)(GPIOA_BASE + 0x00))

/* ADC1 */

#define ADC1_BASE       0x40012000UL

#define ADC_SR          (*(volatile uint32_t *)(ADC1_BASE + 0x00))
#define ADC_CR2         (*(volatile uint32_t *)(ADC1_BASE + 0x08))
#define ADC_SQR3        (*(volatile uint32_t *)(ADC1_BASE + 0x34))
#define ADC_DR          (*(volatile uint32_t *)(ADC1_BASE + 0x4C))

```c
// ADC initialization function
void ADC_Init(void)
{
    RCC_AHB1ENR |= (1U << 0);          // Enable GPIOA peripheral clock

    RCC_APB2ENR |= (1U << 8);          // Enable ADC1 peripheral clock

    GPIOA_MODER |= (3U << (0 * 2));    // Configure PA0 as Analog mode for LM35 sensor

    GPIOA_MODER |= (3U << (1 * 2));    // Configure PA1 as Analog mode for LDR sensor

    ADC_SQR3 = 0;                      // Select ADC Channel 0 as default conversion channel

    ADC_CR2 |= (1U << 0);              // Enable ADC1 peripheral
}

// ADC read function
uint16_t ADC_Read(uint8_t channel)
{
    ADC_SQR3 = channel;                // Select the required ADC channel

    ADC_CR2 |= (1U << 30);             // Start ADC conversion

    while(!(ADC_SR & (1U << 1)));      // Wait until End Of Conversion (EOC) flag is set

    return (uint16_t)ADC_DR;           // Return converted ADC digital value
}
```
