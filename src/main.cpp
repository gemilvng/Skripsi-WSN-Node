// main.cpp

// File header
#include <Arduino.h>
#include <Wire.h>
#include <esp_log.h>

#include "config.h"
#include "pmu.h"
#include "node_identity.h"


void setup() {
    // Initialize I2C communication
    bool i2c_init_status = Wire.begin((int)I2C_SDA, (int)I2C_SCL);

    // Guard clause for I2C init status
    if (!i2c_init_status) {
        ESP_LOGE("Main", "I2C init failed");
        return;
    }

    // Initialize PMU module
    bool pmu_init_status = pmu_init(GNSS_ENABLE_FLAG, LORA_ENABLE_FLAG);
    
    // Guard clause for PMU module init status
    if (!pmu_init_status) {
        ESP_LOGE("Main", "PMU Init failed");
        return;
    }

    // Assign node ID
    node_identity_init();
}

void loop() {
    vTaskDelay(pdMS_TO_TICKS(1000));
    ESP_LOGI("MAIN", "The main program is empty.");
}
