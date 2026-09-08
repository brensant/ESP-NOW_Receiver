#include "receiver.h"

#include <HardwareSerial.h>

t_espnow_data g_data;

void receiveCallback(const uint8_t* mac_addr, const uint8_t* incomingData, int len)
{
	g_data = (*(t_espnow_data*)incomingData);

	Serial.printf("Bytes received: %d\n", len);
	Serial.printf("Value: %d\n", g_data.value);

	switch (g_data.value)
	{
		case true:
			digitalWrite(LED_BUILTIN, HIGH);
			break;
		case false:
			digitalWrite(LED_BUILTIN, LOW);
			break;
	}

	g_data = (t_espnow_data){0};
}

/**
 * Inicializa o ESP-NOW.
 */
esp_err_t initEspNow() {
	if (esp_now_init() != ESP_OK) {
		Serial.println("Erro ao inicializar o ESP-NOW");
		return (ESP_FAIL);
	}

	if (esp_now_register_recv_cb(receiveCallback) != ESP_OK) {
		esp_now_deinit();
		Serial.println("Erro ao registrar callback do receptor");
		return (ESP_FAIL);
	}

	return (ESP_OK);
}
