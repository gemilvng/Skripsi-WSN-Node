// devicePMU.h

#pragma once // Include header file only once during compilation

#define XPOWERS_CHIP_AXP2101

#include <Arduino.h>
#include "XPowersLib.h"

bool deviceInit(bool i2cInitStatus, bool enableGPS, bool enableLoRa);
bool deviceSleep();
