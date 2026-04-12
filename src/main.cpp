// main.cpp

// File header
#include <Arduino.h>
#include <Wire.h>
#include "config.h"
#include "devicePMU.h"
#include <esp_log.h>
#include "sdkconfig.h"

static bool i2cInitStatus;
static bool deviceInitStatus;

void setup() {
    // Initialize I2C communication
    i2cInitStatus = Wire.begin((int)I2C_SDA, (int)I2C_SCL);

    // Guard clause for I2C init status
    if (!i2cInitStatus) {
        ESP_LOGE("Main", "I2C init failed");
        return;
    }

    // Initialize PMU module
    deviceInitStatus = deviceInit(GNSS_ENABLE_FLAG, LORA_ENABLE_FLAG);
    
    // Guard clause for PMU module init status
    if (!deviceInitStatus) {
        ESP_LOGE("Main", "PMU Init failed");
        return;
    }
}

void loop() {
    // To make the board idle without consuming too much power
    vTaskDelay(200000 / portTICK_PERIOD_MS);
}
