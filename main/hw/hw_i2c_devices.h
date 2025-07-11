#pragma once

#include "driver/i2c_master.h"

#include "hw_i2c.h"

#define MPU6050_ADDR 0x68

extern hw_i2c_device mpu6050;
