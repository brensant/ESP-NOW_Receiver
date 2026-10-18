#include "Receiver.h"

#include "Motor.h"
#include "Drive.h"

#include <Arduino.h>
#include <WiFi.h>

// Motor esquerdo
#define LMOTOR_EN_PIN  0
#define LMOTOR_IN1_PIN 1
#define LMOTOR_IN2_PIN 2
#define LMOTOR_PWM_PIN 3

// Motor direito
#define RMOTOR_EN_PIN  4
#define RMOTOR_IN1_PIN 5
#define RMOTOR_IN2_PIN 6
#define RMOTOR_PWM_PIN 7

#define MOTOR_FREQUENCY 500 // ledc frequency (?)

Receiver g_receiver;

Drive g_drive(
	Motor(LMOTOR_EN_PIN, LMOTOR_IN1_PIN, LMOTOR_IN2_PIN, LMOTOR_PWM_PIN),
	Motor(RMOTOR_EN_PIN, RMOTOR_IN1_PIN, RMOTOR_IN2_PIN, RMOTOR_PWM_PIN)
);

void setup()
{
	Serial.begin(9600);
	WiFi.mode(WIFI_STA);

	g_drive.init(MOTOR_FREQUENCY);
	g_receiver.init();
}

void loop()
{
	t_ctrl_pckt pckt;

	if (g_receiver.isLinkAlive() && g_receiver.getLastPacket(pckt)) {
		// Serial.printf("ID:%u  thr:%u  str:%u  W:%d  Wpn:%d  Dir:%d  lost:%lu\n",
		//               pckt.packetId, pckt.throttle, pckt.steering,
		//               pckt.flags.isWheelsEnabled, pckt.flags.isWeaponEnabled,
		//               pckt.flags.weaponDirection, (unsigned long)g_receiver.getLostPackets());

		g_drive.handlePacket(pckt);
	} else {
		g_drive.stop(); // failsafe
	}

	delay(20);
}
