#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/i2c_master.h"

#include "hw_i2c.h"

// static bool transDone(i2c_master_dev_handle_t i2c_dev, const i2c_master_event_data_t *evt_data, void *arg);
// static esp_err_t wait(hw_i2c_device *device);

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

// I2C callback
// const i2c_master_event_callbacks_t cbs = {
//     .on_trans_done = transDone
// };

// static bool IRAM_ATTR transDone(i2c_master_dev_handle_t i2c_dev, const i2c_master_event_data_t *evt_data, void *arg)
// {
//     hw_i2c_device *device = (hw_i2c_device *)arg;
//     BaseType_t pxHigherPriorityTaskWoken = pdFALSE;

//     if (device->running_task != NULL)
//     {
//         vTaskNotifyGiveFromISR(device->running_task, &pxHigherPriorityTaskWoken);
//         portYIELD_FROM_ISR(pxHigherPriorityTaskWoken);
//     }

//     return pxHigherPriorityTaskWoken == pdTRUE;
// }

// static esp_err_t wait(hw_i2c_device *device)
// {
//     ESP_LOGI(TAG, "HI2");
//     ulTaskNotifyTake(pdTRUE, device->timeout_ms);

//     device->running_task = NULL;

//     return ESP_OK;
// }

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
    // ESP_ERROR_CHECK(i2c_master_register_event_callbacks(device->handle, &cbs, device));

    // device->running_task = NULL;

    // device->mutex = xSemaphoreCreateMutex();
    // if (device->mutex == NULL)
    // {
    //     return ESP_FAIL;
    // }

    return ESP_OK;
}

// static esp_err_t hw_i2c_perform_transaction(hw_i2c_device *device, esp_err_t (*transaction_func)(void)) {
//     if (!device || !device->mutex) {
//         return ESP_ERR_INVALID_ARG;
//     }

//     esp_err_t ret = ESP_FAIL;

//     // Wait to acquire the mutex, ensuring exclusive access to the device
//     if (xSemaphoreTake(device->mutex, portMAX_DELAY) == pdTRUE) {
//         // Store the handle of the current task so the ISR knows who to notify
//         device->running_task = xTaskGetCurrentTaskHandle();

//         // Execute the provided I2C transaction function
//         ret = transaction_func();

//         if (ret == ESP_OK) {
//             // Wait for the notification from the ISR.
//             // ulTaskNotifyTake returns the notification count before clearing, or 0 on timeout.
//             if (ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(device->timeout_ms)) == 0) {
//                 ret = ESP_ERR_TIMEOUT;
//                 ESP_LOGW(TAG, "I2C transaction timed out for device 0x%02X", device->config.device_address);
//             }
//         } else {
//             ESP_LOGE(TAG, "I2C transaction failed to start for device 0x%02X, error: %s", device->config.device_address, esp_err_to_name(ret));
//         }

//         // Clear the task handle to prevent accidental notifications
//         device->running_task = NULL;

//         // Release the mutex
//         xSemaphoreGive(device->mutex);
//     } else {
//         ret = ESP_ERR_TIMEOUT; // Failed to acquire mutex
//         ESP_LOGE(TAG, "Failed to acquire mutex for device 0x%02X", device->config.device_address);
//     }

//     return ret;
// }


esp_err_t hw_i2c_writeReg(hw_i2c_device *device, const uint8_t data)
{
    
    
    // Define the specific I2C operation within a lambda function
    // esp_err_t transaction_lambda(void) {
        // The timeout parameter is -1 to make the call non-blocking (asynchronous)
        return i2c_master_transmit(device->handle, &data, 1, device->timeout_ms);
    // }
    // return hw_i2c_perform_transaction(device, transaction_lambda);
    // return wait(device);
}

esp_err_t hw_i2c_writeRegs(hw_i2c_device *device, const uint8_t *data, const uint8_t writeLen)
{
    // Define the specific I2C operation within a lambda function
    // esp_err_t transaction_lambda(void) {
        // The timeout parameter is -1 to make the call non-blocking (asynchronous)
        return i2c_master_transmit(device->handle, data, writeLen, device->timeout_ms);
    // }
    // return hw_i2c_perform_transaction(device, transaction_lambda);
    // return wait(device);
}

esp_err_t hw_i2c_readReg(hw_i2c_device *device, uint8_t *data)
{
    // esp_err_t transaction_lambda(void) {
        return i2c_master_receive(device->handle, data, 1, device->timeout_ms);
    // }
    // return hw_i2c_perform_transaction(device, transaction_lambda);
    // return wait(device);
}

esp_err_t hw_i2c_readRegs(hw_i2c_device *device, const uint8_t *write_buf, uint8_t write_len, uint8_t *read_buf, uint8_t read_len)
{
    // esp_err_t transaction_lambda(void) {
        return i2c_master_transmit_receive(device->handle, write_buf, write_len, read_buf, read_len, device->timeout_ms);
    // }
    // return hw_i2c_perform_transaction(device, transaction_lambda);
    // ESP_LOGI(TAG, "HI");
    // return wait(device);
}