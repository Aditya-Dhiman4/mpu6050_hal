#include "hw_i2c_devices.h"

hw_i2c_device mpu6050 = {
    .config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = MPU6050_ADDR,
        .scl_speed_hz = 100000
    },
    .timeout_ms = portMAX_DELAY,
    // .running_task = NULL,
    // .mutex = NULL
};