// lora_tx_task.cpp

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <esp_log.h>
#include "lora_tx_task.h"
#include "app_queues.h"
#include "packet_types.h"

static void transmit_packets(void* param) {
    network_packet_t pkt;
    for (;;) {
        xQueueReceive(app_queues_outbound(), &pkt, portMAX_DELAY);
        ESP_LOGI("TX", "Dequeued packet originator=0x%04X seq=%u", pkt.sensor_pkt.originator_node_id, pkt.sensor_pkt.sequence_number);
    }
}

void start_lora_tx_task(void) {
    xTaskCreate(
        transmit_packets,
        "Transmit packets",
        4096,
        NULL,
        4,
        NULL
    );
}
