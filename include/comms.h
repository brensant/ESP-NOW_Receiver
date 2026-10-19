#ifndef COMMS_H
# define COMMS_H

# include "esp_now.h"

# include <stdint.h>

# define ESPNOW_CHANNEL 0

# define EMITTER_MAC { 0xA0, 0xA3, 0xB3, 0x29, 0x76, 0xA8 }
# define RECEIVER_MAC { 0xA0, 0xA3, 0xB3, 0x29, 0x38, 0x14 }

typedef struct __attribute__((packed)) s_espnow_data {
	uint16_t packetId;
	uint8_t  throttle; // Y
	uint8_t  steering; // X
	uint8_t  button;   // botão (true/false)
} t_espnow_data;

typedef t_espnow_data t_ctrl_pckt;

// static_assert(sizeof(t_ctrl_pckt) == 5, "t_ctrl_pckt: layout inesperado");

#endif // COMMS_H
