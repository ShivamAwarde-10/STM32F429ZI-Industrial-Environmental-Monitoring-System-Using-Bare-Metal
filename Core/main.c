#include <stdint.h>
#include <stdio.h>

#include "systick.h"
#include "adc.h"
#include "i2c.h"
#include "uart.h"
#include "oled.h"
#include "rtc.h"
#include "LM35.h"
#include "LDR.h"
#include "dashboard.h"

/* Live Expressions */

volatile uint32_t temp;          // Stores temperature value from LM35 sensor

volatile uint16_t light;         // Stores light intensity value from LDR sensor

volatile uint8_t hour;           // Stores current hour from RTC

volatile uint8_t min;            // Stores current minute from RTC

volatile uint8_t sec;            // Stores current second from RTC

RTC_TimeDate_t rtc;              // Structure to store RTC time information

char uart_buffer[64];            // Buffer used to format UART messages

// Main function - Program execution starts from here
int main(void)
{
    SysTick_Init();              // Initialize SysTick timer for delay generation

    ADC_Init();                  // Initialize ADC for LM35 and LDR sensors

    I2C_Init();                  // Initialize I2C for RTC and OLED communication

    UART_Init();                 // Initialize UART for serial communication

    OLED_Init();                 // Initialize SSD1306 OLED display

    OLED_Clear();                // Clear OLED screen before displaying data

    UART_SendString("\r\n");     // Print a blank line on PuTTY terminal

    UART_SendString("================================\r\n");   // Print top separator line

    UART_SendString("STM32 Environmental Monitor\r\n");     // Print project title

    UART_SendString("================================\r\n");   // Print bottom separator line

    while(1)
    {
        temp = LM35_GetTemperature();      // Read temperature from LM35 sensor

        light = LDR_GetValue();            // Read light intensity from LDR sensor

        RTC_GetTime(&rtc);                 // Read current time from DS3231 RTC

        hour = rtc.hour;                   // Copy hour from RTC structure

        min  = rtc.min;                    // Copy minute from RTC structure

        sec  = rtc.sec;                    // Copy second from RTC structure

        Dashboard_Update();                // Update OLED dashboard with latest values

        sprintf(uart_buffer,               // Format sensor and time data into a string
                "TEMP=%lu C  LIGHT=%u  TIME=%02d:%02d:%02d\r\n",
                temp,
                light,
                hour,
                min,
                sec);

        UART_SendString(uart_buffer);      // Send formatted data to PuTTY terminal

        delay_ms(1000);                    // Wait for 1 second before next update
    }
}
```

