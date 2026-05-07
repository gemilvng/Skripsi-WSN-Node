// lora_rx_task.cpp

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <LoraMesher.h>
#include <esp_log.h>
#include "lora_rx_task.h"
#include "lora_radio.h"

static TaskHandle_t ReceiveAppData_TaskHandle = nullptr;

static void receive_packets(void* param) {
    for (;;) {
        ulTaskNotifyTake(pdPASS, portMAX_DELAY);
        while (lora_radio_instance().getReceivedQueueSize() > 0) {
            AppPacket<uint8_t>* packet = lora_radio_instance().getNextAppPacket<uint8_t>();
            ESP_LOGI("RX", "Got packet from 0x%04X size=%u type=0x%02X",  packet->src, packet->payloadSize, packet->payload[0]);
            lora_radio_instance().deletePacket(packet);
        }
    }
}

void start_lora_rx_task(void) {
    xTaskCreate(
        receive_packets,
        "Receive packets",
        4096,
        NULL,
        7,
        &ReceiveAppData_TaskHandle
    );
    lora_radio_instance().setReceiveAppDataTaskHandle(ReceiveAppData_TaskHandle);
}