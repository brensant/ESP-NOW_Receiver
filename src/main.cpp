#include "Receiver.h"

#include <Arduino.h>
#include <WiFi.h>

Receiver g_receiver;

void setup()
{
	Serial.begin(9600);
	WiFi.mode(WIFI_STA);

	g_receiver.init();
}

void loop()
{
	t_ctrl_pckt pckt;

	if (g_receiver.isLinkAlive() && g_receiver.getLastPacket(pckt)) {
		Serial.printf("ID:%u  thr:%u  str:%u  W:%d  Wpn:%d  Dir:%d  lost:%lu\n",
		              pckt.packetId, pckt.throttle, pckt.steering,
		              pckt.flags.isWheelsEnabled, pckt.flags.isWeaponEnabled,
		              pckt.flags.weaponDirection, (unsigned long)g_receiver.getLostPackets());
		// aqui, no futuro: aplicar nos motores
	} else {
		// failsafe: parar motores e arma
	}

	delay(20);
}
