#include "Motor.h"

#include <Arduino.h>

/********************************* LIFECYCLE **********************************/

Motor::Motor(uint8_t en, uint8_t in1, uint8_t in2, uint8_t pwmPin)
  : m_en(en)
  , m_in1(in1)
  , m_in2(in2)
  , m_pwmPin(pwmPin)
  , m_maxDuty(255)
{
}

/************************ NON-STATIC MEMBER FUNCTIONS *************************/

bool Motor::init(uint32_t frequency, uint8_t resolution)
{
	m_maxDuty = (1UL << resolution) - 1;

	pinMode(m_en, OUTPUT);
	pinMode(m_in1, OUTPUT);
	pinMode(m_in2, OUTPUT);

	digitalWrite(m_in1, LOW);
	digitalWrite(m_in2, LOW);
	digitalWrite(m_en, HIGH);

	if (!ledcAttach(m_pwmPin, frequency, resolution)) {
		Serial.printf("Falha ao configurar o PWM no pino %d\n", m_pwmPin);
		return (false);
	}

	stop();

	Serial.println("Motor initialized:");
	Serial.printf("\tEN_PIN: %d\n", m_en);
	Serial.printf("\tIN1_PIN: %d\n", m_in1);
	Serial.printf("\tIN2_PIN: %d\n", m_in2);
	Serial.printf("\tPWM_PIN: %d\n", m_pwmPin);

	return (true);
}

void Motor::forward(uint8_t speed)
{
	digitalWrite(m_in1, HIGH);
	digitalWrite(m_in2, LOW);

	writePwm(speed);
}

void Motor::backward(uint8_t speed)
{
	digitalWrite(m_in1, LOW);
	digitalWrite(m_in2, HIGH);

	writePwm(speed);
}

void Motor::setSpeed(int16_t speed)
{
	int32_t s = speed;

	if (s > 0)
		forward(s > 255 ? 255 : s);
	else if (s < 0)
		backward(-s > 255 ? 255 : -s);
	else
		stop();
}

void Motor::stop()
{
	digitalWrite(m_in1, LOW);
	digitalWrite(m_in2, LOW);

	writePwm(0);
}

/****************************** HELPER FUNCTIONS ******************************/

/**
 * Converte 0..255 para 0..m_maxDuty, independente da resolução configurada.
 */
void Motor::writePwm(uint8_t speed)
{
	ledcWrite(m_pwmPin, (uint32_t)speed * m_maxDuty / 255);
}
