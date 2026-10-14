# STM32-l476rg-SEN0142

A driver for the DFRobot SEN0142 sensor, written for the STM32 NUCLEO-L476RG
board using STM32CubeIDE and the STM32 HAL library.

The project communicates with the sensor over I2C and outputs the measured
values over [UART / debugger / etc.].

## Hardware
- STM32 NUCLEO-L476RG
- DFRobot SEN0142 sensor module

## Wiring (I2C)

| SEN0142 pin | Nucleo pin | Note                 |
|-------------|------------|----------------------|
| VCC         | 3V3 or 5V  | Check module rating  |
| GND         | GND        |                      |
| SDA         | PB9 (D14)  | I2C1_SDA             |
| SCL         | PB8 (D15)  | I2C1_SCL             |

I2C address: `0x68`

Pull-up resistors on SDA and SCL are required. Most breakout modules
include them. If yours does not, add 4.7 kΩ resistors to 3V3.

## Project structure
The STM32CubeIDE project is located in the `SEN0142/` folder.
The CubeMX configuration is in `SEN0142/SEN0142.ioc`.

## Build and flash
1. Open STM32CubeIDE and choose **File → Open Projects from File System**.
2. Select the `SEN0142/` folder.
3. Build the project (Ctrl+B) and flash it to the board.

## Usage
[Describe how to read the sensor, e.g. which function to call and what it returns.]

## License
MIT
