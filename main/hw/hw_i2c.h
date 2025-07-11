#pragma once

#include <stdbool.h>

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "esp_err.h"
#include "driver/i2c_types.h"

#include "hw_i2c.h"

// I2C0 bus registers 
#define I2C0_SDA 21
#define I2C0_SCL 22

// I2C0 bus config
#define I2C0_GLITCH_IGNORE_CNT 7
#define I2C0_INTERNAL_PULLUP true

// #ifdef I2C_NUM_1

// // I2C1 bus registers 
// #define I2C1_SDA 21
// #define I2C1_SCL 22

// // I2C0 bus config
// #define I2C1_GLITCH_IGNORE_CNT 7
// #define I2C1_INTERNAL_PULLUP true
// #endif

typedef struct 
{
    i2c_master_dev_handle_t handle;
    const i2c_device_config_t config;
    const int timeout_ms;
    TaskHandle_t running_task;
    SemaphoreHandle_t mutex;
} hw_i2c_device;

esp_err_t hw_i2c_registerBuses(void);

esp_err_t hw_i2c_addDevice(hw_i2c_device *device);

esp_err_t hw_i2c_writeReg(hw_i2c_device *device, const uint8_t data);

esp_err_t hw_i2c_writeRegs(hw_i2c_device *device, const uint8_t *write, const uint8_t writeLen);

esp_err_t hw_i2c_readReg(hw_i2c_device *device, uint8_t *data);

esp_err_t hw_i2c_readRegs(hw_i2c_device *device, const uint8_t *write, const uint8_t writeLen, uint8_t *read, const uint8_t readLen);

