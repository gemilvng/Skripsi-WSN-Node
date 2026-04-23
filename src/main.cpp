// main.cpp

// File header
#include <Arduino.h>
#include <Wire.h>
#include <esp_log.h>

#include "config.h"
#include "pmu.h"
#include "node_identity.h"


void setup() {
    ESP_LOGI("Main", "Reset reason: %d", esp_reset_reason());
    // Initialize I2C communication
    bool i2c_init_status = Wire.begin((int)I2C_SDA, (int)I2C_SCL);

    // Guard clause for I2C init status
    if (!i2c_init_status) {
        ESP_LOGE("Main", "I2C init failed. Restarting in 3s ...");
        vTaskDelay(pdMS_TO_TICKS(3000));
        esp_restart();
    }

    // PMU module setup
    bool pmu_setup_status = pmu_setup(GNSS_ENABLE_FLAG, LORA_ENABLE_FLAG);
    
    // Guard clause for PMU module setup status
    if (!pmu_setup_status) {
        ESP_LOGE("Main", "PMU setup failed. Restarting in 3s ...");
        vTaskDelay(pdMS_TO_TICKS(3000));
        esp_restart();
    }

    // Assign node ID
    node_identity_init();
}

void loop() {
    vTaskDelay(pdMS_TO_TICKS(60000));
    ESP_LOGI("MAIN", "The main program is empty.");
}
