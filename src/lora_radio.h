// lora_radio.h

#pragma once // Include header file only once during compilation

#include <LoraMesher.h> 

LoraMesher& lora_radio_instance(void); 
void lora_radio_begin(void);
void lora_radio_start(void);
