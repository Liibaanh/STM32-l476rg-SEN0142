# STM32-l476rg-SEN0142

An I2C driver for the DFRobot SEN0142 6-axis IMU (MPU6050: 3-axis accelerometer,
3-axis gyroscope and temperature sensor), written for the STM32 NUCLEO-L476RG
using STM32CubeIDE and the STM32 HAL library.

## Features
- Accelerometer readings in g
- Gyroscope readings in °/s
- Internal temperature in °C
- Device ID check during initialization

## Hardware
- STM32 NUCLEO-L476RG
- DFRobot SEN0142 (MPU6050) module

## Wiring (I2C)

| SEN0142 pin | Nucleo pin | Note                |
|-------------|------------|---------------------|
| VCC         | 3V3 or 5V  | Check module rating |
| GND         | GND        |                     |
| SDA         | PB9 (D14)  | I2C1_SDA            |
| SCL         | PB8 (D15)  | I2C1_SCL            |

I2C address: `0x68` (7-bit; `0x69` if AD0 is pulled high).
The driver shifts it left by one bit for the STM32 HAL.

## Project structure
The STM32CubeIDE project is located in the `SEN0142/` folder.
The CubeMX configuration is in `SEN0142/SEN0142.ioc`.

## Build and flash
1. Open STM32CubeIDE and choose **File → Open Projects from File System**.
2. Select the `SEN0142/` folder.
3. Build the project (Ctrl+B) and flash it to the board.

## API

| Function | Description |
|----------|-------------|
| `int MPU6050_Init(void)` | Initializes the sensor and checks its ID. Returns 0 on success. |
| `void MPU6050_Read_Accel(float *Ax, float *Ay, float *Az)` | Reads acceleration in g. |
| `void MPU6050_Read_Gyro(float *Gx, float *Gy, float *Gz)` | Reads rotation rate in °/s. |
| `void MPU6050_Read_Temp(float *temp)` | Reads internal temperature in °C. |
| `uint8_t MPU6050_I2C_Read(uint8_t reg)` | Reads one byte from a register. |
| `void MPU6050_I2C_Write(uint8_t reg, uint8_t data)` | Writes one byte to a register. |

Global variables `accel_x/y/z`, `gyro_x/y/z` and `temperature` are declared
in the header for convenience.

## Usage

```c
#include "mpu6050.h"

if (MPU6050_Init() != 0) {
    // Sensor not found, check wiring and I2C address
}

while (1) {
    MPU6050_Read_Accel(&accel_x, &accel_y, &accel_z);
    MPU6050_Read_Gyro(&gyro_x, &gyro_y, &gyro_z);
    MPU6050_Read_Temp(&temperature);
    HAL_Delay(100);
}
```

## License
MIT
