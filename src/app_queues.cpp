// app_queues.cpp

#include "app_queues.h"
#include "config.h"
#include "packet_types.h"

static QueueHandle_t outbound_queue;
static QueueHandle_t uplink_queue;
static QueueHandle_t log_queue;

void app_queues_init(void) {
    outbound_queue = xQueueCreate(OUTBOUND_QUEUE_SIZE, sizeof(network_packet_t));
    configASSERT(outbound_queue != NULL);

    uplink_queue = xQueueCreate(UPLINK_QUEUE_SIZE, sizeof(network_packet_t));
    configASSERT(uplink_queue != NULL);
    // TODO: create log_queue once log_entry_t is defined (logger module postponed)
}

QueueHandle_t app_queues_outbound(void) {
    return outbound_queue;
}

QueueHandle_t app_queues_uplink(void) {
    return uplink_queue;   
}

QueueHandle_t app_queues_log(void) {
    return log_queue;
}

bool app_queues_put_drop_oldest(QueueHandle_t q, const void* item, size_t item_size) {
    BaseType_t result = xQueueSend(q, item, 0);
    if (result == pdPASS) {
        return true;
    } else {
        constexpr size_t MAX_ITEM_SIZE = 256;
        uint8_t scratch[MAX_ITEM_SIZE];
        configASSERT(item_size <= MAX_ITEM_SIZE);
        xQueueReceive(q, scratch, 0);
        return xQueueSend(q, item, 0) == pdPASS;
    }
}
