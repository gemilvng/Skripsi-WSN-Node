// lora_radio.cpp

#include "config.h"
#include "lora_radio.h"
#include <LoraMesher.h>
#include <SPI.h>

LoraMesher& lora_radio_instance(void) {
    return LoraMesher::getInstance();
}

void lora_radio_begin(void){

    // Access and modify LoRaMesher configuration parameter
    LoraMesher::LoraMesherConfig config = LoraMesher::LoraMesherConfig();
    config.loraCs = LORA_PIN_CS;
    config.loraIrq = LORA_PIN_DIO0;
    config.loraRst = LORA_PIN_RST;
    config.loraIo1 = LORA_PIN_DIO1;
    config.module = LoraMesher::LoraModules::SX1276_MOD;
    config.spi = &SPI;
    config.freq = LORA_FREQ_MHZ;
    config.bw = LORA_BW_KHZ;
    config.sf = LORA_SF;
    config.cr = LORA_CR;
    config.syncWord = LM_SYNC_WORD;
    config.power = LORA_TX_POWER_DBM;
    config.preambleLength = LM_PREAMBLE_LENGTH;
    config.max_packet_size = LM_MAX_PACKET_SIZE;
    lora_radio_instance().begin(config);
}

void lora_radio_start(void){
    lora_radio_instance().start();
}
