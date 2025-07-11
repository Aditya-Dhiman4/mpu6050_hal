#include "esp_log.h"
#include "driver/i2c_master.h"

#include "io_mpu6050.h"

#include "hw_i2c_devices.h"
#include "hw_i2c.h"

esp_err_t io_mpu6050_init(void)
{
    ESP_ERROR_CHECK(hw_i2c_addDevice(&mpu6050));

    uint8_t wakeBuf[] = {PWR_MGMT_1, 0x00};
    ESP_ERROR_CHECK(hw_i2c_writeRegs(&mpu6050, wakeBuf, sizeof(wakeBuf)));

    uint8_t write[] = {MPU6050_ADDR};
    uint8_t read;
    ESP_ERROR_CHECK(hw_i2c_readRegs(&mpu6050, write, 1, &read, 1));

    if (read == 0x00) {
        ESP_LOGI(TAG, "Successfully woke sensor: 0x%02X", read);
    } else {
        ESP_LOGI(TAG, "Failed to wake up sensor: 0x%02X", read);
        return ESP_FAIL;
    }

    uint8_t accelConfigBuf[] = {ACCEL_CONFIG, ACCEL_CONFIG_BITS};
    hw_i2c_writeRegs(&mpu6050, accelConfigBuf, sizeof(accelConfigBuf));

    uint8_t gyroConfigBuf[] = {GYRO_CONFIG, GYRO_CONFIG_BITS};
    hw_i2c_writeRegs(&mpu6050, gyroConfigBuf, sizeof(gyroConfigBuf));

    return ESP_OK;
}

// void io_mpu6050_calibrate(void)
// {

// }

void io_mpu6050_getAccel(AccelData *data)
{
    AccelDataRaw rawData;    
    uint8_t accel_reg_addr = ACCEL_XOUT_H;

    ESP_ERROR_CHECK(hw_i2c_readRegs(&mpu6050, &accel_reg_addr, 1, (uint8_t *)&rawData, sizeof(rawData)));

    int16_t xRaw = (int16_t)(rawData.x_h << 8 | rawData.x_l);
    int16_t yRaw = (int16_t)(rawData.y_h << 8 | rawData.y_l);
    int16_t zRaw = (int16_t)(rawData.z_h << 8 | rawData.z_l);
    
    data->x = ACCEL_SCALE(xRaw);
    data->y = ACCEL_SCALE(yRaw);
    data->z = ACCEL_SCALE(zRaw);
}

void io_mpu6050_getGyro(GyroData *data)
{
    GyroDataRaw rawData;
    uint8_t gyro_reg_addr = GYRO_XOUT_H;

    ESP_ERROR_CHECK(hw_i2c_readRegs(&mpu6050, &gyro_reg_addr, 1, (uint8_t *)&rawData, sizeof(rawData)));

    int16_t xRaw = (int16_t)(rawData.x_h << 8 | rawData.x_l);
    int16_t yRaw = (int16_t)(rawData.y_h << 8 | rawData.y_l);
    int16_t zRaw = (int16_t)(rawData.z_h << 8 | rawData.z_l);
    
    data->x = GYRO_SCALE(xRaw);
    data->y = GYRO_SCALE(yRaw);
    data->z = GYRO_SCALE(zRaw);
}

void io_mpu6050_getTemp(TempData *data)
{
    TempDataRaw rawData;
    uint8_t tempRegAddr = TEMP_OUT_H;

    ESP_ERROR_CHECK(hw_i2c_readRegs(&mpu6050, &tempRegAddr, 1, (uint8_t *)&rawData, sizeof(rawData)));

    int16_t tempRaw = (int16_t)(rawData.t_h << 8 | rawData.t_l);
    
    data->temp = TEMP_SCALE(tempRaw);
}