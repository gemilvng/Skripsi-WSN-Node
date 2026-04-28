// sensor_task.cpp

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "sensor_task.h"
#include "config.h"
#include "node_identity.h"
#include "packet_types.h"
#include "app_queues.h"

static void sensor_reading(void* param) {
    static uint8_t sequence = 0;
    for (;;) {
        vTaskDelay(pdMS_TO_TICKS(SENSING_INTERVAL_MS));
        network_packet_t network_pkt;
        network_pkt.sensor_pkt.packet_type = PKT_TYPE_SENSOR_DATA;
        network_pkt.sensor_pkt.originator_node_id = node_identity_get();
        network_pkt.sensor_pkt.sequence_number = sequence;
        network_pkt.sensor_pkt.measurement_age_s = 0;
        network_pkt.sensor_pkt.sensor_type = 0x01;
        network_pkt.sensor_pkt.sensor_payload = sequence;
        network_pkt.measurement_timestamp_ms = millis();
        app_queues_put_drop_oldest(app_queues_outbound(), &network_pkt, sizeof(network_pkt));
        sequence++;
    }
}

void start_sensor_task(void) {
    xTaskCreate(
        sensor_reading,
        "Sensor reading",
        4096,
        NULL,
        2,
        NULL
    );
}