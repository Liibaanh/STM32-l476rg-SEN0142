#include "SEN0142.h"
#include "stdio.h"
#include "string.h"

// External peripheral handles
extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart2;

/**
 * @brief Read a single byte from an 8-bit register on the MPU6050.
 * @param reg Register address to read from.
 * @return The value read from the register.
 */
uint8_t MPU6050_I2C_Read(uint8_t reg)
{
    uint8_t data = 0;

    HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR_I2C, reg, I2C_MEMADD_SIZE_8BIT, &data, 1, 1000);

    return data;
}

/**
 * @brief Write a single byte to an 8-bit register on the MPU6050.
 * @param reg Register address to write to.
 * @param data Value to write.
 */
void MPU6050_I2C_Write(uint8_t reg, uint8_t data)
{
    HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR_I2C, reg, I2C_MEMADD_SIZE_8BIT, &data, 1, 1000);
}

/**
 * @brief Initialize the MPU6050 sensor, verify its WHO_AM_I ID, and configure power and sample rates.
 * @return 0 on success.
 */
int MPU6050_Init(void)
{
    uint8_t check, data;

    // Check device identification register (WHO_AM_I)
    HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR_I2C, WHO_AM_I, 1, &check, 1, 1000);

    // MPU6050 default WHO_AM_I response is 0x68 (decimal 104)
    if (check == 104)
    {
        // Wake up the sensor (clear sleep bit in PWR_MGMT_1)
        data = 0;
        HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR_I2C, PWR_MGMT_1, 1, &data, 1, 1000);

        // Set sample rate divider
        data = 0x07;
        HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR_I2C, SMPLRT_DIV_REG, 1, &data, 1, 1000);

        // Configure Gyroscope scale
        data = 0x00;
        HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR_I2C, GYRO_CONFIG, 1, &data, 1, 1000);

        // Configure Accelerometer scale
        data = 0x00;
        HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR_I2C, ACCEL_CONFIG, 1, &data, 1, 1000);
    }

    return 0;
}

/**
 * @brief Read accelerometer data for X, Y, and Z axes.
 * @param Ax Pointer to store acceleration along X-axis (g).
 * @param Ay Pointer to store acceleration along Y-axis (g).
 * @param Az Pointer to store acceleration along Z-axis (g).
 */
void MPU6050_Read_Accel(float *Ax, float *Ay, float *Az)
{
    uint8_t accel_data[6];
    int16_t accel_x_raw, accel_y_raw, accel_z_raw;

    // Read 6 consecutive bytes starting from ACCEL_XOUT_H
    HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR_I2C, ACCEL_XOUT_H, I2C_MEMADD_SIZE_8BIT,
                     accel_data, 6, 1000);

    // Combine high and low bytes into 16-bit signed raw values
    accel_x_raw = (int16_t)((accel_data[0] << 8) | accel_data[1]);
    accel_y_raw = (int16_t)((accel_data[2] << 8) | accel_data[3]);
    accel_z_raw = (int16_t)((accel_data[4] << 8) | accel_data[5]);

    // Convert raw values to g using the sensitivity scale factor
    *Ax = accel_x_raw / ACCEL_SENS_2G;
    *Ay = accel_y_raw / ACCEL_SENS_2G;
    *Az = accel_z_raw / ACCEL_SENS_2G;
}

/**
 * @brief Read gyroscope data for X, Y, and Z axes.
 * @param Gx Pointer to store rotation rate around X-axis (°/s).
 * @param Gy Pointer to store rotation rate around Y-axis (°/s).
 * @param Gz Pointer to store rotation rate around Z-axis (°/s).
 */
void MPU6050_Read_Gyro(float *Gx, float *Gy, float *Gz)
{
    uint8_t gyro_data[6];
    int16_t gyro_x_raw, gyro_y_raw, gyro_z_raw;

    // Read 6 consecutive bytes starting from GYRO_XOUT_H
    HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR_I2C, GYRO_XOUT_H, I2C_MEMADD_SIZE_8BIT,
                     gyro_data, 6, 1000);

    // Combine high and low bytes into 16-bit signed raw values
    gyro_x_raw = (int16_t)((gyro_data[0] << 8) | gyro_data[1]);
    gyro_y_raw = (int16_t)((gyro_data[2] << 8) | gyro_data[3]);
    gyro_z_raw = (int16_t)((gyro_data[4] << 8) | gyro_data[5]);

    // Convert raw values to degrees per second (°/s) using the sensitivity scale factor
    *Gx = gyro_x_raw / GYRO_SENS_250;
    *Gy = gyro_y_raw / GYRO_SENS_250;
    *Gz = gyro_z_raw / GYRO_SENS_250;
}

/**
 * @brief Read internal temperature sensor data.
 * @param temps Pointer to store the temperature in degrees Celsius (°C).
 */
void MPU6050_Read_Temp(float *temps)
{
    uint8_t temp_data[2];
    int16_t temp_raw;

    // Read 2 bytes starting from TEMP_OUT_H
    HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR_I2C, TEMP_OUT_H, I2C_MEMADD_SIZE_8BIT,
                     temp_data, 2, 1000);

    // Combine high and low bytes into a 16-bit signed raw value
    temp_raw = (int16_t)((temp_data[0] << 8) | temp_data[1]);

    // Convert raw value to temperature according to datasheet formula: (raw / 340) + 36.6
    *temps = (temp_raw / 340.0f) + 36.6f;
}
