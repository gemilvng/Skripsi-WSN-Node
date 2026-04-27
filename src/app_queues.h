// app_queues.h

#pragma once // Include header file only once during compilation

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <stddef.h>

void app_queues_init(void);

QueueHandle_t app_queues_outbound(void);

QueueHandle_t app_queues_uplink(void);

QueueHandle_t app_queues_log(void);

bool app_queues_put_drop_oldest(QueueHandle_t q, const void* item, size_t item_size);

// TODO: Implement stats_counter_t parameter, dependent on stats module.