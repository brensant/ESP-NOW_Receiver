#include "Drive.h"

/********************************* LIFECYCLE **********************************/

Drive::Drive(Motor motorLeft, Motor motorRight)
  : m_motorLeft(motorLeft)
  , m_motorRight(motorRight)
{
}

/************************ NON-STATIC MEMBER FUNCTIONS *************************/

bool Drive::init(uint32_t frequency, uint8_t resolution)
{
	bool isLeftOk = m_motorLeft.init(frequency, resolution);
	bool isRightOk = m_motorRight.init(frequency, resolution);

	return (isLeftOk && isRightOk);
}

void Drive::stop()
{
	m_motorLeft.stop();
	m_motorRight.stop();
}

/**
 * Lida com os pacotes ESP-NOW que chegam pelo controle remoto.
 */
void Drive::handlePacket(const t_ctrl_pckt &packet)
{
	int32_t throttle = axisToSpeed(packet.throttle);
	int32_t steering = axisToSpeed(packet.steering);

	int32_t left = throttle + steering;
	int32_t right = throttle - steering;

	// Se passar de 255, escala as duas rodas pelo mesmo fator para manter a curva.
	int32_t absLeft = left < 0 ? -left : left;
	int32_t absRight = right < 0 ? -right : right;
	int32_t peak = absLeft > absRight ? absLeft : absRight;

	if (peak > 255) {
		left = left * 255 / peak;
		right = right * 255 / peak;
	}

	m_motorLeft.setSpeed(left * MAX_SPEED / 255);
	m_motorRight.setSpeed(right * MAX_SPEED / 255);
}

int32_t Drive::axisToSpeed(uint8_t raw)
{
	int32_t speed = ((int32_t)raw - 128) * 255 / 127;

	if (speed > 255)
		speed = 255;
	if (speed < -255)
		speed = -255;

	return (speed);
}
