#include "receiver.h"

#include <HardwareSerial.h>
#include <WiFi.h>

void setup()
{
	Serial.begin(9600);
	WiFi.mode(WIFI_STA);
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);

	if (initEspNow() != ESP_OK)
		return;
}

void loop() { }
