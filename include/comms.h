#ifndef COMMS_H
# define COMMS_H

# include "esp_now.h"

# include <stdint.h>

# define ESPNOW_CHANNEL 0

# define EMITTER_MAC { 0xA0, 0xA3, 0xB3, 0x29, 0x76, 0xA8 }
# define RECEIVER_MAC { 0xA0, 0xA3, 0xB3, 0x29, 0x38, 0x14 }

typedef struct __attribute__((packed)) s_flags {
	unsigned int isWheelsEnabled: 1;
	unsigned int isWeaponEnabled: 1;
	unsigned int weaponDirection: 1;
} t_flags;

typedef struct __attribute__((packed)) s_espnow_data {
	uint16_t packetId;
	uint8_t  throttle; // Y
	uint8_t  steering; // X
	t_flags  flags;
} t_espnow_data;

typedef t_espnow_data t_ctrl_pckt;

#endif // COMMS_H
