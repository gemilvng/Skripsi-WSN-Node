// config.h

#pragma once // Include header file only once during compilation

// File Header
#include <Arduino.h>

// I2C configuration with I2C default pin in ESP32 Arduino Core
#define I2C_SDA SDA
#define I2C_SCL SCL

// Module configuration flag for AXP2101
#define GNSS_ENABLE_FLAG false
#define LORA_ENABLE_FLAG true