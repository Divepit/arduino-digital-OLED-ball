# Arduino UNO OLED/IMU digital ball simulation

Arduino + OLED + IMU simulation that renders a single ball moving with gravity based on live accelerometer data.

## Overview

This project reads acceleration from an I2C IMU (address `0x68`) and simulates a particle constrained to a `128x64` OLED display (`SSD1306`, address `0x3C`). Tilting the device changes gravity direction, and the ball slides accordingly.

## Features

- Real-time 2D particle simulation driven by accelerometer input
- OLED rendering using Adafruit GFX + SSD1306 libraries
- Wall constraints to keep the particle inside screen bounds
- Simple physics integration with linear drag

## Hardware

- Arduino Uno (configured in `platformio.ini`)
- SSD1306 OLED display (`128x64`, I2C, `0x3C`)
- MPU6050-compatible IMU (`0x68`) or equivalent with matching register map
- Jumper wires and common ground

## Wiring (Uno, I2C)

- `A4` -> `SDA` (OLED + IMU)
- `A5` -> `SCL` (OLED + IMU)
- `3.3V` -> `VCC` (OLED + IMU)
- `GND` -> `GND` (OLED + IMU)

Both devices share the same I2C bus.

## Software Stack

- C++ (Arduino framework)
- PlatformIO
- `Adafruit GFX Library`
- `Adafruit SSD1306`
- `Wire` (I2C)

## Build and Upload

From the project root:

```bash
pio run
pio run -t upload
```

## Configuration

Useful constants:

- `SCREEN_WIDTH`, `SCREEN_HEIGHT`, `BALL_RADIUS` in `src/main.cpp`
- `PIXELS_PER_METER_X`, `PIXELS_PER_METER_Y`, `IMU_ADDR` in `include/simulation.h`
- `MAX_PARTICLES` in `include/simulation.h` (currently `1`)

## AI Declaration

This is an educational project for myself, so I wrote all of it manually and used AI for code review / sparring to learn about inefficiencies and where I can improve. The readme was mostly generated using OpenAI Codex.