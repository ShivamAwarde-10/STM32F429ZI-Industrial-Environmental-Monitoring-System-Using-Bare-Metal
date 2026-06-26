#include "gpio.h"

```c
// Enable GPIO peripheral clock
static void GPIO_EnableClock(GPIO_TypeDef *GPIOx)
{
    if(GPIOx == GPIOA)
    {
        RCC->AHB1ENR |= (1U << 0);          // Enable clock for GPIOA
    }
    else if(GPIOx == GPIOB)
    {
        RCC->AHB1ENR |= (1U << 1);          // Enable clock for GPIOB
    }
    else if(GPIOx == GPIOC)
    {
        RCC->AHB1ENR |= (1U << 2);          // Enable clock for GPIOC
    }
    else if(GPIOx == GPIOD)
    {
        RCC->AHB1ENR |= (1U << 3);          // Enable clock for GPIOD
    }
    else if(GPIOx == GPIOE)
    {
        RCC->AHB1ENR |= (1U << 4);          // Enable clock for GPIOE
    }
}

// GPIO initialization function
void GPIO_Init(GPIO_TypeDef *GPIOx,
               uint8_t pin,
               uint8_t mode)
{
    GPIO_EnableClock(GPIOx);                        // Enable clock for selected GPIO port

    GPIOx->MODER &= ~(3U << (pin * 2));             // Clear existing mode bits of selected pin

    GPIOx->MODER |= ((mode & 0x03U) << (pin * 2));  // Configure required GPIO mode
}

// Set GPIO pin High
void GPIO_SetPin(GPIO_TypeDef *GPIOx,
                 uint8_t pin)
{
    GPIOx->BSRR = (1U << pin);                      // Set selected GPIO pin
}

// Set GPIO pin Low
void GPIO_ClearPin(GPIO_TypeDef *GPIOx,
                   uint8_t pin)
{
    GPIOx->BSRR = (1U << (pin + 16));               // Reset selected GPIO pin
}

// Toggle GPIO pin state
void GPIO_TogglePin(GPIO_TypeDef *GPIOx,
                    uint8_t pin)
{
    GPIOx->ODR ^= (1U << pin);                      // Toggle selected GPIO output pin
}

// Read GPIO pin state
uint8_t GPIO_ReadPin(GPIO_TypeDef *GPIOx,
                     uint8_t pin)
{
    return (uint8_t)((GPIOx->IDR >> pin) & 0x01);  // Return current logic level of selected pin
}
```
