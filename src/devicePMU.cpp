// devicePMU.cpp

#include "devicePMU.h"

XPowersPMU devicePMU;

bool deviceInit(bool i2cInitStatus, bool enableGPS, bool enableLoRa){

    if (!i2cInitStatus) {
        // Will be defined later
    }

    bool pmuInitStatus = devicePMU.init();

    if (!pmuInitStatus) {
        // Will be defined later
    }

    // DCDC1 power channel config (ESP32)
    devicePMU.setDC1Voltage(3300);
    devicePMU.setProtectedChannel(XPOWERS_DCDC1);

    // ALDO2 power channel config (LoRa)
    if (enableLoRa) {
        devicePMU.setALDO2Voltage(3300);
        devicePMU.enableALDO2();
    } else {
        devicePMU.disableALDO2();
    }

    // ALDO3 power channel config (NEO-6M)
    if (enableGPS) {
        devicePMU.setALDO3Voltage(3300);
        devicePMU.enableALDO3();
    } else {
        devicePMU.disableALDO3();
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
}
