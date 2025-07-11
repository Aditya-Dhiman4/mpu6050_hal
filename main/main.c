#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_task_wdt.h"
#include "driver/i2c_master.h"

// io
#include "io_mpu6050.h"

// hw
#include "hw_i2c.h"

// Task functions
void mpu6050Task_run(void *args);

// mpu6050 task setup
TaskFunction_t mpu6050Task_func = mpu6050Task_run;
const char *const mpu6050Task_name = "mpu6050 Task";
const configSTACK_DEPTH_TYPE mpu6050Task_stackDepth = 4096;
void *mpu6050Task_pvParameters = NULL;
UBaseType_t mpu6050Task_priority = tskIDLE_PRIORITY;
TaskHandle_t mpu6050Task_handle = NULL;

// Prototypes
void TWDT_init(void);
void I2C_init(void);

void app_main() 
{
    // Initialize peripherals
    TWDT_init();
    I2C_init();

    // Add to watchdog
    ESP_ERROR_CHECK(esp_task_wdt_add(NULL));
    ESP_ERROR_CHECK(esp_task_wdt_status(NULL));
    
    xTaskCreate(mpu6050Task_func, mpu6050Task_name, mpu6050Task_stackDepth, mpu6050Task_pvParameters, mpu6050Task_priority, &mpu6050Task_handle);

    for (;;)
    {
        
        ESP_ERROR_CHECK(esp_task_wdt_reset());
        vTaskDelay(pdMS_TO_TICKS(500));
    }

}

void TWDT_init(void)
{
    ESP_ERROR_CHECK(esp_task_wdt_deinit());
    
    esp_task_wdt_config_t wdtConfig = {
        .timeout_ms = 1000,
        .idle_core_mask = (1 << CONFIG_FREERTOS_NUMBER_OF_CORES) - 1,
        .trigger_panic = true
    };
    
    ESP_ERROR_CHECK(esp_task_wdt_init(&wdtConfig));
}

void I2C_init(void)
{
    hw_i2c_registerBuses();
}

void mpu6050Task_run(void *args)
{
    ESP_ERROR_CHECK(esp_task_wdt_add(NULL));
    ESP_ERROR_CHECK(esp_task_wdt_status(NULL));
    
    TickType_t ticks = xTaskGetTickCount();
    const TickType_t period = pdMS_TO_TICKS(10);
        
    ESP_ERROR_CHECK(io_mpu6050_init());

    for (;;)
    {   
        AccelData accelData;
        GyroData gyroData;

        io_mpu6050_getAccel(&accelData);
        io_mpu6050_getGyro(&gyroData);

        ESP_LOGI(
            mpu6050Task_name, 
            "ACCEL --- X:%.2f, Y:%.2f, Z:%.2f ||| GYRO --- X:%.2f, Y:%.2f, Z:%.2f", 
            accelData.x, accelData.y, accelData.z, 
            gyroData.x, gyroData.y, gyroData.z
        );

        ticks += period;
        ESP_ERROR_CHECK(esp_task_wdt_reset());
        vTaskDelayUntil(&ticks, period);
    }
    
}

