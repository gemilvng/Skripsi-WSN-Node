// pmu.cpp

#include "pmu.h"
#include "XPowersLib.h"

XPowersPMU device_pmu;

bool pmu_init(bool enable_gps_flag, bool enable_lora_flag){

    bool pmu_init_status = device_pmu.init();

    // Guard clause for PMU init status
    if (!pmu_init_status) {
        ESP_LOGE("PMU", "AXP2101 initialization failed");
        return false;
    }

    if (device_pmu.isEnableDC1()) {
        uint16_t vDCDC1 = device_pmu.getDC1Voltage();
        ESP_LOGI("PMU", "DCDC1 channel for ESP32 SoC is on. Channel voltage: %u mV", vDCDC1);
    }

    // Set DCDC1 always on for ESP32
    device_pmu.setProtectedChannel(XPOWERS_DCDC1);

    // ALDO2 power channel config (for Semtech SX1276 LoRa module)
    if (enable_lora_flag) {
        device_pmu.setALDO2Voltage(3300);
        device_pmu.enableALDO2();
        uint16_t vALDO2 = device_pmu.getALDO2Voltage();
        ESP_LOGI("PMU", "ALDO2 channel for LoRa module is on. Channel voltage: %u mV", vALDO2);
    } else {
        device_pmu.disableALDO2();
        ESP_LOGI("PMU", "ALDO2 channel for LoRa module is off");
    }

    // ALDO3 power channel config (for NEO-6M GNSS module)
    if (enable_gps_flag) {
        device_pmu.setALDO3Voltage(3300);
        device_pmu.enableALDO3();
        device_pmu.setButtonBatteryChargeVoltage(3300);
        device_pmu.enableButtonBatteryCharge();
        uint16_t vALDO3 = device_pmu.getALDO3Voltage();
        uint16_t vBACKUP = device_pmu.getButtonBatteryVoltage();
        ESP_LOGI("PMU", "ALDO3 channel for GPS module is on. Channel voltage: %u mV", vALDO3);
        ESP_LOGI("PMU", "vBACKUP channel for GPS module is on. Channel voltage: %u mV", vBACKUP);
    } else {
        device_pmu.disableALDO3();
        device_pmu.disableButtonBatteryCharge();
        ESP_LOGI("PMU", "ALDO3 channel for GPS module is off");
        ESP_LOGI("PMU", "VBACKUP channel for GPS module is off");
    }

    // Disable unused channel
    device_pmu.disableDC2();
    device_pmu.disableDC3();
    device_pmu.disableDC4();
    device_pmu.disableDC5();
    device_pmu.disableALDO1();
    device_pmu.disableALDO4();
    device_pmu.disableBLDO1();
    device_pmu.disableBLDO2();
    device_pmu.disableDLDO1();
    device_pmu.disableDLDO2();

    return true;
}
