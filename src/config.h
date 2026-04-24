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

// LoRa network configuration
#define LM_BAND 921.900F
#define LM_POWER 8
#define LM_DUTY_CYCLE 100

// LoRa pin interface (LilyGo T-Beam V1.2, SX1276)
#define LORA_PIN_SCLK = 5
#define LORA_PIN_MISO = 19
#define LORA_PIN_MOSI = 27
#define LORA_PIN_CS   = 18
#define LORA_PIN_RST  = 23
#define LORA_PIN_DIO0 = 26