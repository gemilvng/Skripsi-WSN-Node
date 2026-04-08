// main.cpp

// File header
#include <Arduino.h>
#include "config.h"
#include "devicePMU.h"

void setup() {
    bool enableGPSFlag = false;
    bool enableLoRaFlag = true;
    bool i2cInitStatus = Wire.begin((int)I2C_SDA, (int)I2C_SCL);

    // Initialize AXP2101 module
    deviceInit(i2cInitStatus, enableGPSFlag, enableLoRaFlag);
}

void loop() {

}
