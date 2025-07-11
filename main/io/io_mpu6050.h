#pragma once

#include <stdint.h>
#include <math.h>

#define TAG "mpu6050"

// ========== Device Address ==========
#define MPU6050_ADDR     0x68  // 7-bit I2C address of the MPU-6050

// ========== Scale Factors ==========
// Choose scaling factor
#define ACCEL_FACTOR_4G
#define GYRO_FACTOR_500S

#ifdef ACCEL_FACTOR_2G
#define ACCEL_FACTOR 2.0f
#define ACCEL_CONFIG_BITS 0x00
#endif
#ifdef ACCEL_FACTOR_4G
#define ACCEL_FACTOR 4.0f
#define ACCEL_CONFIG_BITS 0x08
#endif
#ifdef ACCEL_FACTOR_8G
#define ACCEL_FACTOR 8.0f
#define ACCEL_CONFIG_BITS 0x10
#endif
#ifdef ACCEL_FACTOR_16G
#define ACCEL_FACTOR 16.0f
#define ACCEL_CONFIG_BITS 0x18
#endif

#ifdef GYRO_FACTOR_250S
#define GYRO_FACTOR 250.0f
#define GYRO_CONFIG_BITS 0x00
#endif
#ifdef GYRO_FACTOR_500S
#define GYRO_FACTOR 500.0f
#define GYRO_CONFIG_BITS 0x08
#endif
#ifdef GYRO_FACTOR_1000S
#define GYRO_FACTOR 1000.0f
#define GYRO_CONFIG_BITS 0x10
#endif
#ifdef GYRO_FACTOR_2000S
#define GYRO_FACTOR 2000.0f
#define GYRO_CONFIG_BITS 0x18
#endif

#define ACCEL_SCALE(accel)   ((float)((accel) * (ACCEL_FACTOR / 32768.0f) * 9.81f))      
#define GYRO_SCALE(gyro)  ((float)((gyro) *(GYRO_FACTOR / 32768.0f) * (M_PI / 180.0f)))
#define TEMP_SCALE(temp)       ((float)(((temp) * (1.0f / 340.0f)) + 36.35))

// ========== Core Configuration Registers ==========
#define SMPLRT_DIV       0x19  // Sample Rate Divider
#define CONFIG           0x1A  // DLPF_CFG and external sync

// ========== Gyro & Accel Configuration ==========
#define GYRO_CONFIG      0x1B  // Full-scale range & self-test
#define ACCEL_CONFIG     0x1C  // Full-scale range & self-test

// ========== FIFO & I²C-Master Control ==========
#define FIFO_EN          0x23  // Enable FIFO for sensor data
#define I2C_MST_CTRL     0x24  // I2C Master control

// I2C Slave 0–4 registers
#define I2C_SLV0_ADDR    0x25  // Slave 0 I2C address
#define I2C_SLV0_REG     0x26  // Slave 0 register pointer
#define I2C_SLV0_CTRL    0x27  // Slave 0 control (enable, length)

#define I2C_SLV1_ADDR    0x28
#define I2C_SLV1_REG     0x29
#define I2C_SLV1_CTRL    0x2A

#define I2C_SLV2_ADDR    0x2B
#define I2C_SLV2_REG     0x2C
#define I2C_SLV2_CTRL    0x2D

#define I2C_SLV3_ADDR    0x2E
#define I2C_SLV3_REG     0x2F
#define I2C_SLV3_CTRL    0x30

#define I2C_SLV4_ADDR    0x31
#define I2C_SLV4_REG     0x32
#define I2C_SLV4_DO      0x33  // Data out to slave 4
#define I2C_SLV4_CTRL    0x34
#define I2C_SLV4_DI      0x35  // Data in from slave 4

#define I2C_MST_STATUS   0x36  // I2C Master status

// ========== Interrupt Configuration ==========
#define INT_PIN_CFG      0x37  // INT pin / bypass enable configuration
#define INT_ENABLE       0x38  // Interrupt enable bits
#define INT_STATUS       0x3A  // Interrupt status bits

// ========== Data Registers (Accel, Temp, Gyro) ==========
// Accelerometer output, registers 0x3B–0x40
#define ACCEL_XOUT_H     0x3B
#define ACCEL_XOUT_L     0x3C
#define ACCEL_YOUT_H     0x3D
#define ACCEL_YOUT_L     0x3E
#define ACCEL_ZOUT_H     0x3F
#define ACCEL_ZOUT_L     0x40

// Temperature output, registers 0x41–0x42
#define TEMP_OUT_H       0x41
#define TEMP_OUT_L       0x42

// Gyroscope output, registers 0x43–0x48
#define GYRO_XOUT_H      0x43
#define GYRO_XOUT_L      0x44
#define GYRO_YOUT_H      0x45
#define GYRO_YOUT_L      0x46
#define GYRO_ZOUT_H      0x47
#define GYRO_ZOUT_L      0x48

// ========== External Sensor Data (Aux I²C) ==========
#define EXT_SENS_DATA_00 0x49  // Data from external sensors (aux I2C), bytes 0–23
#define EXT_SENS_DATA_01 0x4A
#define EXT_SENS_DATA_02 0x4B
#define EXT_SENS_DATA_03 0x4C
#define EXT_SENS_DATA_04 0x4D
#define EXT_SENS_DATA_05 0x4E
#define EXT_SENS_DATA_06 0x4F
#define EXT_SENS_DATA_07 0x50
#define EXT_SENS_DATA_08 0x51
#define EXT_SENS_DATA_09 0x52
#define EXT_SENS_DATA_10 0x53
#define EXT_SENS_DATA_11 0x54
#define EXT_SENS_DATA_12 0x55
#define EXT_SENS_DATA_13 0x56
#define EXT_SENS_DATA_14 0x57
#define EXT_SENS_DATA_15 0x58
#define EXT_SENS_DATA_16 0x59
#define EXT_SENS_DATA_17 0x5A
#define EXT_SENS_DATA_18 0x5B
#define EXT_SENS_DATA_19 0x5C
#define EXT_SENS_DATA_20 0x5D
#define EXT_SENS_DATA_21 0x5E
#define EXT_SENS_DATA_22 0x5F
#define EXT_SENS_DATA_23 0x60

// ========== FIFO Count & Read/Write ==========
#define FIFO_COUNTH      0x72  // FIFO message count high byte
#define FIFO_COUNTL      0x73  // FIFO message count low byte
#define FIFO_R_W         0x74  // FIFO read/write register

// ========== User Control, Signal Path, Power Management ==========
#define SIGNAL_PATH_RESET 0x68 // Reset gyro, accel, and temp signal paths
#define USER_CTRL         0x6A // FIFO and I2C master enable/reset
#define PWR_MGMT_1        0x6B // Device reset, sleep, clock select
#define PWR_MGMT_2        0x6C // Enable/disable standby per axis

// ========== Device ID ==========
#define WHO_AM_I          0x75 // Should return 0x68 (MPU6050_ADDR)

typedef struct __attribute__((packed))
{
    uint8_t x_h;
    uint8_t x_l;
    uint8_t y_h;
    uint8_t y_l;
    uint8_t z_h;
    uint8_t z_l;
} AccelDataRaw;

typedef struct __attribute__((packed))
{
    uint8_t x_h;
    uint8_t x_l;
    uint8_t y_h;
    uint8_t y_l;
    uint8_t z_h;
    uint8_t z_l;
} GyroDataRaw;

typedef struct __attribute__((packed))
{
    uint8_t t_h;
    uint8_t t_l;
} TempDataRaw;

typedef struct
{
    float x, y, z;
} AccelData;

typedef struct
{
    float x, y, z;
} GyroData;

typedef struct
{
    float temp;
} TempData;

esp_err_t io_mpu6050_init(void);

void io_mpu6050_calibrate(void);

void io_mpu6050_getAccel(AccelData *data);

void io_mpu6050_getGyro(GyroData *data);

void io_mpu6050_getTemp(TempData *data);