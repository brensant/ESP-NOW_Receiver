#ifndef COMMS_H
# define COMMS_H

# include "esp_now.h"

# include <stdint.h>

# define ESPNOW_CHANNEL 0

# define EMITTER_MAC { 0xA0, 0xA3, 0xB3, 0x29, 0x76, 0xA8 }
# define RECEIVER_MAC { 0xA0, 0xA3, 0xB3, 0x29, 0x38, 0x14 }

typedef struct s_espnow_data {
	uint8_t value;
} t_espnow_data;

#endif // COMMS_H
