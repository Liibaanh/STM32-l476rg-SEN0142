#ifndef INC_SEN0142_H_
#define INC_SEN0142_H_

#include "stm32l4xx_hal.h"

#define MPU6050_ADDR        0x68
#define MPU6050_ADDR_I2C    (0x68 << 1) // Shifted left by 1 for STM32 HAL (0xD0 for write)


// MPU6050 Register Map

#define SMPLRT_DIV_REG      0x19
#define WHO_AM_I            0x75
#define GYRO_CONFIG         0x1B
#define ACCEL_CONFIG        0x1C
#define PWR_MGMT_1          0x6B

// Accelerometer Data Registers

#define ACCEL_XOUT_H        0x3B
#define ACCEL_XOUT_L        0x2C
#define ACCEL_YOUT_H        0x3D
#define ACCEL_YOUT_L        0x3E
#define ACCEL_ZOUT_H        0x3F
#define ACCEL_ZOUT_L        0x40

// Gyroscope Data Registers

#define GYRO_XOUT_H         0x43
#define GYRO_XOUT_L         0x44
#define GYRO_YOUT_H         0x45
#define GYRO_YOUT_L         0x46
#define GYRO_ZOUT_H         0x47
#define GYRO_ZOUT_L         0x48


// Temperature Data Registers

#define TEMP_OUT_H          0x41
#define TEMP_OUT_L          0x42

// Gyroscope Full Scale Range Configurations
#define GYRO_250DPS         0x00
#define GYRO_500DPS         0x08
#define GYRO_1000DPS        0x10
#define GYRO_2000DPS        0x18

// Accelerometer Full Scale Range Configurations
#define ACCEL_2G            0x00
#define ACCEL_4G            0x08
#define ACCEL_8G            0x10
#define ACCEL_16G           0x18


// Gyroscope Sensitivity Scale Factors (LSB/(°/s))
#define GYRO_SENS_250       131.0f
#define GYRO_SENS_500       65.5f
#define GYRO_SENS_1000      32.8f
#define GYRO_SENS_2000      16.4f

// Accelerometer Sensitivity Scale Factors (LSB/g)
#define ACCEL_SENS_2G       16384.0f
#define ACCEL_SENS_4G       8192.0f
#define ACCEL_SENS_8G       4096.0f
#define ACCEL_SENS_16G      2048.0f


// Public Function Prototypes


/**
 * @brief Read a single byte from an 8-bit register.
 * @param reg Register address.
 * @return Value read from the register.
 */
uint8_t MPU6050_I2C_Read(uint8_t reg);

/**
 * @brief Write a single byte to an 8-bit register.
 * @param reg Register address.
 * @param data Value to write.
 */
void MPU6050_I2C_Write(uint8_t reg, uint8_t data);

/**
 * @brief Initialize the MPU6050 sensor and check its ID.
 * @return 0 on success.
 */
int MPU6050_Init(void);

/**
 * @brief Read X, Y, and Z accelerometer values in g.
 * @param Ax Pointer to X-axis acceleration.
 * @param Ay Pointer to Y-axis acceleration.
 * @param Az Pointer to Z-axis acceleration.
 */
void MPU6050_Read_Accel(float *Ax, float *Ay, float *Az);

/**
 * @brief Read X, Y, and Z gyroscope values in °/s.
 * @param Gx Pointer to X-axis rotation rate.
 * @param Gy Pointer to Y-axis rotation rate.
 * @param Gz Pointer to Z-axis rotation rate.
 */
void MPU6050_Read_Gyro(float *Gx, float *Gy, float *Gz);

/**
 * @brief Read internal temperature in degrees Celsius.
 * @param temp Pointer to store temperature.
 */
void MPU6050_Read_Temp(float *temp);


// Global Variable Declarations

extern float accel_x, accel_y, accel_z;
extern float gyro_x, gyro_y, gyro_z;
extern float temperature;

#endif /* INC_SEN0142_H_ */
