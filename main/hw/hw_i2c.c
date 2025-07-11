#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/i2c_master.h"

#include "hw_i2c.h"

static const char *TAG = "hw_i2c";

// I2C buses
static i2c_master_bus_handle_t i2c0_handle;
static const i2c_master_bus_config_t i2c0_config = {
    .i2c_port = I2C_NUM_0,
    .sda_io_num = I2C0_SDA,
    .scl_io_num = I2C0_SCL,
    .clk_source = I2C_CLK_SRC_DEFAULT,
    .glitch_ignore_cnt = I2C0_GLITCH_IGNORE_CNT,
    .flags.enable_internal_pullup = I2C0_INTERNAL_PULLUP,
    .trans_queue_depth = 0
};

esp_err_t hw_i2c_registerBuses(void)
{
    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c0_config, &i2c0_handle));
    return ESP_OK;
}

esp_err_t hw_i2c_addDevice(hw_i2c_device *device)
{
    if (device == NULL)
    {
        return ESP_FAIL;
    }
    
    ESP_ERROR_CHECK(i2c_master_bus_add_device(i2c0_handle, &device->config, &device->handle));

    return ESP_OK;
}

esp_err_t hw_i2c_writeReg(hw_i2c_device *device, const uint8_t data)
{
    return i2c_master_transmit(device->handle, &data, 1, device->timeout_ms);
}

esp_err_t hw_i2c_writeRegs(hw_i2c_device *device, const uint8_t *data, const uint8_t writeLen)
{
    return i2c_master_transmit(device->handle, data, writeLen, device->timeout_ms);
}

esp_err_t hw_i2c_readReg(hw_i2c_device *device, uint8_t *data)
{
    return i2c_master_receive(device->handle, data, 1, device->timeout_ms);
}

esp_err_t hw_i2c_readRegs(hw_i2c_device *device, const uint8_t *write_buf, uint8_t write_len, uint8_t *read_buf, uint8_t read_len)
{
    return i2c_master_transmit_receive(device->handle, write_buf, write_len, read_buf, read_len, device->timeout_ms);
}