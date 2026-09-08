#ifndef RECEIVER_H
# define RECEIVER_H

# include "comms.h"
# include "esp_now.h"

# include <stdint.h>

void receiveCallback(const uint8_t* mac_addr, const uint8_t* incomingData, int len);

esp_err_t initEspNow();

extern t_espnow_data g_data;

#endif // RECEIVER_H
