// node_identity.cpp

#include "node_identity.h"
#include <esp_mac.h>
#include <esp_log.h>

static uint16_t node_id = 0; // Variable to store node ID

void node_identity_init(void) {
    
    // Array to store each MAC address bytes
    uint8_t mac_address[6];

    // Get the MAC address of ESP32
    esp_err_t err = esp_read_mac(mac_address, ESP_MAC_WIFI_STA);

    // Guard clause of MAC address retrieval process
    if (err != ESP_OK) {
        ESP_LOGE("NODE_ID", "Failed to retrieve MAC address as Node ID");
        return;
    }

    // Shift the 5th byte to the upper-half, let the rest filled by 6th byte
    node_id = (mac_address[4] << 8) | mac_address[5];
    ESP_LOGI("NODE_ID", "Node ID: 0x%04X", node_id);
}

uint16_t node_identity_get(void) {
    return node_id;
}
