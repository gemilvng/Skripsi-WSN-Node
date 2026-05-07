// main.cpp

// File header
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <esp_log.h>

#include "config.h"
#include "pmu.h"
#include "node_identity.h"
#include "lora_radio.h"
#include "app_queues.h"
#include "sensor_task.h"


void setup() {

    ESP_LOGI("Main", "Reset reason: %d", esp_reset_reason());

    // I2C setup
    bool i2c_init_status = Wire.begin((int)I2C_SDA, (int)I2C_SCL);

    // Guard clause for I2C init status
    if (!i2c_init_status) {
        ESP_LOGE("Main", "I2C init failed. Restarting in 3s ...");
        vTaskDelay(pdMS_TO_TICKS(3000));
        esp_restart();
    }

    // SPI setup
    SPI.begin(LORA_PIN_SCLK, LORA_PIN_MISO, LORA_PIN_MOSI, LORA_PIN_CS);

    // PMU module setup
    bool pmu_setup_status = pmu_setup(GNSS_ENABLE_FLAG, LORA_ENABLE_FLAG);
    
    // Guard clause for PMU module setup status
    if (!pmu_setup_status) {
        ESP_LOGE("Main", "PMU setup failed. Restarting in 3s ...");
        vTaskDelay(pdMS_TO_TICKS(3000));
        esp_restart();
    }

    // Node configuration and initialization
    node_identity_init();
    app_queues_init();
    lora_radio_begin();
    lora_radio_start();

    // For testing purpose
    if (node_identity_get() == 0) {
        lora_radio_instance().addGatewayRole();
        ESP_LOGI("Main", "Bring-up: this node acts as gateway");
    }

    start_sensor_task();
}

void loop() {
    vTaskDelay(pdMS_TO_TICKS(60000));
    ESP_LOGI("MAIN", "The main program is empty.");
}
