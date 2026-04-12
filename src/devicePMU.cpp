// devicePMU.cpp

#include "devicePMU.h"

XPowersPMU devicePMU;

bool deviceInit(bool enableGPSFlag, bool enableLoRaFlag){

    bool pmuInitStatus = devicePMU.init();

    if (!pmuInitStatus) {
        ESP_LOGE("PMU", "AXP2101 initialization failed");
        return false;
    }

    if (devicePMU.isEnableDC1()) {
        uint16_t vDCDC1 = devicePMU.getDC1Voltage();
        ESP_LOGI("PMU", "DCDC1 channel for ESP32 SoC is on. Channel voltage: %u mV", vDCDC1);
    }

    // Set DCDC1 always on for ESP32
    devicePMU.setProtectedChannel(XPOWERS_DCDC1);

    // ALDO2 power channel config (for Semtech SX1276 LoRa module)
    if (enableLoRaFlag) {
        devicePMU.setALDO2Voltage(3300);
        devicePMU.enableALDO2();
        uint16_t vALDO2 = devicePMU.getALDO2Voltage();
        ESP_LOGI("PMU", "ALDO2 channel for LoRa module is on. Channel voltage: %u mV", vALDO2);
    } else {
        devicePMU.disableALDO2();
        ESP_LOGI("PMU", "ALDO2 channel for LoRa module is off");
    }

    // ALDO3 power channel config (for NEO-6M GNSS module)
    if (enableGPSFlag) {
        devicePMU.setALDO3Voltage(3300);
        devicePMU.enableALDO3();
        devicePMU.setButtonBatteryChargeVoltage(3300);
        devicePMU.enableButtonBatteryCharge();
        uint16_t vALDO3 = devicePMU.getALDO3Voltage();
        uint16_t vBACKUP = devicePMU.getButtonBatteryVoltage();
        ESP_LOGI("PMU", "ALDO3 channel for GPS module is on. Channel voltage: %u mV", vALDO3);
        ESP_LOGI("PMU", "vBACKUP channel for GPS module is on. Channel voltage: %u mV", vBACKUP);
    } else {
        devicePMU.disableALDO3();
        devicePMU.disableButtonBatteryCharge();
        ESP_LOGI("PMU", "ALDO3 channel for GPS module is off");
        ESP_LOGI("PMU", "VBACKUP channel for GPS module is off");
    }

    // Disable unused channel
    devicePMU.disableDC2();
    devicePMU.disableDC3();
    devicePMU.disableDC4();
    devicePMU.disableDC5();
    devicePMU.disableALDO1();
    devicePMU.disableALDO4();
    devicePMU.disableBLDO1();
    devicePMU.disableBLDO2();
    devicePMU.disableDLDO1();
    devicePMU.disableDLDO2();

    return true;
}
