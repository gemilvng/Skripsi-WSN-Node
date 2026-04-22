// node_identity.h

#pragma once // Include header file only once during compilation

#include <stdint.h> // Needed for types like uint*_t

void node_identity_init(void);

uint16_t node_identity_get(void);