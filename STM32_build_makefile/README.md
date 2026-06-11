# STM32 Bare-metal Build System with Makefile

A complete bare-metal build system for STM32F103 (ARM Cortex-M3) built from scratch — no IDE, no HAL, no auto-generated code.

## Overview

This project demonstrates a full understanding of the ARM Cortex-M3 build pipeline and memory architecture by manually implementing every layer: startup code, linker script, Makefile, and peripheral drivers.

## Features

- Full build pipeline automated via Makefile: `.c` → `.i` → `.s` → `.o` → `.elf` → `.hex`
- Custom linker script defining FLASH and SRAM memory regions and section placement
- Custom startup file handling vector table, stack pointer initialization, and `.data` copy from FLASH to SRAM
- Bare-metal peripheral drivers: GPIO, EXTI, Timer, RCC
- ARM GCC toolchain integrated into VS Code with MSYS2 on Windows

## Technical Highlights

- Wrote Makefile to automate the full build pipeline from source to flashable `.hex` binary
- Created linker script (`.ld`) defining FLASH/SRAM memory regions and section placement (`.text`, `.data`, `.bss`)
- Implemented startup file (`startup.c`) handling vector table, stack pointer initialization, and copying `.data` from FLASH to SRAM
- Mapped overall memory layout: vector table at `0x08000000` (FLASH), stack at top of SRAM
- Integrated ARM GCC toolchain into VS Code with MSYS2 for building via Makefile on Windows

## Memory Layout

```
FLASH (0x08000000)          SRAM (0x20000000)
┌─────────────────┐         ┌─────────────────┐
│   Vector Table  │         │      Stack       │ ← top of SRAM
├─────────────────┤         ├─────────────────┤
│   .text (code)  │         │      Heap        │
├─────────────────┤         ├─────────────────┤
│   .data (init)  │ ──────► │   .data (RAM)   │
├─────────────────┤         ├─────────────────┤
│   .rodata       │         │      .bss        │
└─────────────────┘         └─────────────────┘
```

## Project Structure

```
STM32_build_makefile/
├── Core/
│   └── main.c              # Application entry point
├── Driver/
│   ├── Inc/                # Header files (GPIO, EXTI, TIM, RCC, AFIO)
│   └── Src/                # Driver source files
├── Startup/
│   └── stm32_startup.c     # Vector table, stack init, data/bss init
├── Linker/
│   └── stm_ls.ld           # Custom linker script
├── Output/                 # Build artifacts (.o, .elf, .hex, .map)
└── Makefile                # Build automation
```

## Technologies Used

| Category | Details |
|---|---|
| Language | Embedded C |
| MCU | STM32F103C8 (ARM Cortex-M3) |
| Toolchain | ARM GCC (arm-none-eabi) |
| Build System | Makefile |
| IDE | VS Code + MSYS2 on Windows |
| Flash Tool | ST-Link |

## How to Build

```bash
# Build the project
make

# Clean build artifacts
make clean
```
