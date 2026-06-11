# STM32 Digital Clock

A digital clock firmware developed on STM32F103 (ARM Cortex-M3) using bare-metal driver implementation — no HAL, no BSP.

## Features

- Display time (HH-MM-SS) and date (DD-MM-YY) on TFT 1.8'' LCD via SPI
- Button 1: Toggle between time and date display (EXTI interrupt)
- Button 2: Turn off / turn on the display (EXTI interrupt)
- Set date and time via UART serial communication from PC terminal
- Real-time clock using DS3231 RTC module via I2C

## Technical Highlights

- Built custom peripheral driver libraries from scratch using base address + offset to access peripheral registers via pointer casting
- Configured Timer interrupt (1-second tick) to trigger TFT display refresh for real-time clock update
- Handled button press via EXTI interrupt with hardware debounce circuit to eliminate contact bouncing
- Used UART DMA to independently receive date/time data from PC without blocking the main loop
- Debugged hardware issues using 8CH 24MHz Logic Analyzer to capture and verify UART/I2C/SPI signal waveforms
- Traced register-level bugs using Keil C debugger (watch window, breakpoints, peripheral register view)

## Project Structure

```
STM32_Digital_clock/
├── Core/               # Application layer (main, button, display, UART tasks)
├── Driver/             # Bare-metal peripheral drivers (GPIO, UART, I2C, SPI, Timer, EXTI, DMA, ADC)
├── Lib/                # External module libraries (DS3231 RTC, TFT LCD, Font)
├── RTE/                # Keil runtime environment files
└── digital_clock.uvprojx  # Keil MDK project file
```

## Technologies Used

| Category | Details |
|---|---|
| Language | Embedded C |
| MCU | STM32F103C8 (ARM Cortex-M3) |
| Protocols | UART, I2C, SPI |
| Peripherals | GPIO, Timer, EXTI, DMA, ADC |
| Tools | Keil C, ST-Link, 8CH 24MHz Logic Analyzer |

## Hardware

- STM32F103C8T6 (Blue Pill)
- DS3231 RTC module (I2C)
- TFT 1.8'' LCD display (SPI)
- 2x Push buttons with hardware debounce circuit
- USB-UART converter for serial communication
