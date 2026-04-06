// main.cpp

// File header
#include <Arduino.h>
#include <Wire.h>
#include "config.h"

void setup() {
    // Initialize I2C as master-assigned node
    Wire.begin((int)I2C_SDA, (int)I2C_SCL);
}

void loop() {

}