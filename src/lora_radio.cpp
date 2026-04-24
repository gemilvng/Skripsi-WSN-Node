// lora_radio.cpp

#include "config.h"
#include <LoraMesher.h>

void lora_radio_begin(void){

    // Access and modify LoRaMesher configuration parameter
    LoraMesher::LoraMesherConfig config = LoraMesher::LoraMesherConfig();
    config.loraCs = LORA_PIN_CS;
    config.loraIrq = LORA_PIN_DIO0;
    config.loraRst = LORA_PIN_RST;
    config.loraIo1 = LORA_PIN_DIO1;
    config.module = LoraMesher::LoraModules::SX1276_MOD;
    config.freq = LORA_FREQ_MHZ;
    config.cr = LORA_CR;
    config.syncWord = LM_SYNC_WORD;
    config.power = LORA_TX_POWER_DBM;
    config.preambleLength = LM_PREAMBLE_LENGTH;
    config.max_packet_size = LM_MAX_PACKET_SIZE;
}