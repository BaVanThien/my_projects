# STM32 Snake Game with FreeRTOS

A real-time Snake game developed on STM32F103 (ARM Cortex-M3) using FreeRTOS — two-task architecture with bare-metal SPI driver for TFT LCD display.

---

## Features

- Real-time Snake game running on TFT 1.8'' LCD (128x160) via SPI
- Two-task FreeRTOS architecture: game logic and button input run independently
- 4-direction control via push buttons (UP / DOWN / LEFT / RIGHT)
- Food generation at random positions on the grid
- Wall and self-collision detection with game-over screen
- Restart game on any key press after game-over

---

## Technical Highlights

- Designed two-task FreeRTOS architecture: `vTaskSnake` (priority 2) for game logic and `vTaskInput` (priority 3) for button polling every 5ms
- Used Mutex (`xSnakeMutex`, `xLcdMutex`) to protect shared resources: snake state data and SPI LCD bus from concurrent access between tasks
- Used Event Group (`xDirectionEvent`) with 4 direction bits (UP/DOWN/LEFT/RIGHT) to signal direction changes from input task to game task at 60ms game tick
- Implemented software debounce: required 2 consecutive stable GPIO reads before registering button press to eliminate contact bouncing
- Wrote bare-metal SPI driver for ST7735 TFT LCD (128x160); rendered pixel blocks and strings for real-time game display update

---

## Project Structure

```
STM32_Snake_Game_FreeRTOS/
├── App/                # Application layer (game logic, snake task, input task)
├── Core/               # MCU core configuration (system clock, startup)
├── Driver/             # Bare-metal peripheral drivers (GPIO, SPI, Timer)
├── Lib/                # External libraries (ST7735 LCD driver, Font)
└── freertos/           # FreeRTOS kernel source (tasks, mutex, event group)
```

---

## Technologies Used

| Category    | Details                                              |
|-------------|------------------------------------------------------|
| Language    | Embedded C                                           |
| MCU         | STM32F103C8 (ARM Cortex-M3)                          |
| RTOS        | FreeRTOS (Task, Mutex, Event Group)                  |
| Protocols   | SPI                                                  |
| Peripherals | GPIO, Timer                                          |
| Tools       | Keil MDK, ST-Link                                    |

---

## Hardware

- STM32F103C8T6 (Blue Pill)
- TFT 1.8'' LCD display ST7735 (128x160, SPI)
- 4x Push buttons (UP / DOWN / LEFT / RIGHT)