// packet_types.h

#pragma once // Include header file only once during compilation

#include <stdint.h>

enum packet_type_t : uint8_t {
    PKT_TYPE_SENSOR_DATA = 0x01,
};

struct __attribute__((packed)) sensor_packet_t {
    uint8_t packet_type;
    uint16_t originator_node_id;
    uint8_t sequence_number;
    uint16_t measurement_age_s;
    uint8_t sensor_type;
    uint32_t sensor_payload;
};

struct network_packet_t {
    sensor_packet_t packet;
    uint32_t measurement_timestamp_ms;
};

