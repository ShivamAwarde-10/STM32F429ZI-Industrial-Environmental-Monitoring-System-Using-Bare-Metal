# STM32F429ZI-Industrial-Environmental-Monitoring-System-Using-Bare-Metal
Industrial Environmental Monitoring and Data Logging System developed using Bare-Metal Embedded C on STM32F429ZI, featuring GPIO, SysTick, ADC, UART, I2C, RTC, OLED, EEPROM, Watchdog, and real-time sensor monitoring.

# Industrial Environmental Monitoring and Data Logging System

### Bare-Metal Embedded Firmware Development on STM32F429ZI

## Project Overview

This project demonstrates the development of a real-time Industrial Environmental Monitoring and Data Logging System using Bare-Metal Embedded C on the STM32F429ZI (ARM Cortex-M4) microcontroller.

The objective of this project is to design reusable peripheral drivers from scratch through direct register programming and integrate them into a modular embedded firmware application without using STM32 HAL or CubeMX-generated peripheral libraries.

---

## Features

* Bare-Metal Embedded C Programming
* Register-Level Peripheral Configuration
* Modular Driver Architecture
* GPIO Driver
* SysTick Driver
* ADC Driver
* UART Driver
* I2C Driver
* SSD1306 OLED Driver
* DS3231 RTC Driver
* AT24C32 EEPROM Driver
* LM35 Temperature Sensor Interface
* LDR Sensor Interface
* Independent Watchdog (IWDG)
* UART Command Console
* Real-Time Environmental Monitoring Dashboard

---

## Hardware Used

* STM32 NUCLEO-F429ZI Development Board
* SSD1306 OLED Display (I2C)
* DS3231 RTC Module
* AT24C32 EEPROM
* LM35 Temperature Sensor
* LDR Sensor
* USB-UART Interface
* PuTTY Terminal

---

## Software Used

* STM32CubeIDE
* Embedded C
* Git
* GitHub
* PuTTY

---

## Folder Structure

```
Project
│
├── Application
│   ├── dashboard.c
│   └── main.c
│
├── Drivers
│   ├── gpio
│   ├── systick
│   ├── adc
│   ├── uart
│   ├── i2c
│   ├── rtc
│   ├── oled
│   ├── eeprom
│   ├── lm35
│   ├── ldr
│   └── iwdg
│
├── Inc
├── Src
├── Images
├── Videos
└── README.md
```

---

## Functional Overview

* Reads temperature using LM35 through ADC
* Reads light intensity using LDR through ADC
* Retrieves current time from DS3231 RTC
* Displays real-time information on SSD1306 OLED
* Stores configuration using AT24C32 EEPROM
* Provides UART debugging and command console
* Uses Independent Watchdog for firmware reliability

---

## UART Commands

```
TEMP
LIGHT
TIME
HELP
```

---

## Skills Demonstrated

* Embedded C
* Bare-Metal Programming
* ARM Cortex-M4
* STM32F429ZI
* Register-Level Programming
* Peripheral Driver Development
* GPIO
* ADC
* UART
* I2C
* RTC
* EEPROM
* OLED Display
* Watchdog Timer
* Sensor Interfacing
* Real-Time Embedded Systems
* Firmware Debugging
* Modular Driver Development

---

## Future Improvements

* SPI Driver
* CAN Communication
* RS485 Communication
* SD Card Data Logging
* ESP8266 Wi-Fi Connectivity

---

## Author

Shivam

Embedded Systems | Embedded Firmware | Bare-Metal Embedded C | STM32
