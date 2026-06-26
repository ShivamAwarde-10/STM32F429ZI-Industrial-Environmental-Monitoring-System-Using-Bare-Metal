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

volatile uint32_t temp;
volatile uint16_t light;

volatile uint8_t hour;
volatile uint8_t min;
volatile uint8_t sec;

RTC_TimeDate_t rtc;

char uart_buffer[64];

int main(void)
{
    /* System Drivers */
    SysTick_Init();

    ADC_Init();

    I2C_Init();

    UART_Init();

    /* Display */
    OLED_Init();

    OLED_Clear();

    UART_SendString("\r\n");
    UART_SendString("================================\r\n");
    UART_SendString("STM32 Environmental Monitor\r\n");
    UART_SendString("================================\r\n");

    while(1)
    {
        /* Sensor Readings */
        temp = LM35_GetTemperature();

        light = LDR_GetValue();

        /* RTC Read */
        RTC_GetTime(&rtc);

        hour = rtc.hour;
        min  = rtc.min;
        sec  = rtc.sec;

        /* OLED Dashboard */
        Dashboard_Update();

        /* UART Debug Output */
        sprintf(uart_buffer,
                "TEMP=%lu C  LIGHT=%u  TIME=%02d:%02d:%02d\r\n",
                temp,
                light,
                hour,
                min,
                sec);

        UART_SendString(uart_buffer);

        delay_ms(1000);
    }
}
