#include "Motor.h"

#include <HardwareSerial.h>

/*********************************** TYPES ************************************/

/********************************* LIFECYCLE **********************************/

Motor::Motor(uint8_t en, uint8_t in1, uint8_t in2, uint8_t pwmChannel)
  : m_en(en)
  , m_in1(in1)
  , m_in2(in2)
  , m_pwmChannel(pwmChannel)
{
	Serial.println("Motor initialized:");
	Serial.printf("EN_PIN: ", m_en);
	Serial.printf("IN1_PIN: ", m_in1);
	Serial.printf("IN2_PIN: ", m_in2);
	Serial.printf("PWM_PIN: ", m_pwmChannel);
}

Motor::~Motor()
{
}

/************************** STATIC MEMBER FUNCTIONS ***************************/

/************************ NON-STATIC MEMBER FUNCTIONS *************************/

void Motor::begin(uint32_t frequency, uint8_t resolution)
{
	pinMode(m_in1, OUTPUT);
	pinMode(m_in2, OUTPUT);

	ledcSetup(m_pwmChannel, frequency, resolution);
	ledcAttachPin(m_en, m_pwmChannel);

	stop();
}

void Motor::forward(uint8_t speed)
{
	digitalWrite(m_in1, HIGH);
	digitalWrite(m_in2, LOW);

	ledcWrite(m_pwmChannel, speed);
}

void Motor::backward(uint8_t speed)
{
	digitalWrite(m_in1, LOW);
	digitalWrite(m_in2, HIGH);

	ledcWrite(m_pwmChannel, speed);
}

void Motor::stop()
{
	digitalWrite(m_in1, LOW);
	digitalWrite(m_in2, LOW);

	ledcWrite(m_pwmChannel, 0);
}

/* OPERATORS */

/****************************** HELPER FUNCTIONS ******************************/

/* OPERATORS */
