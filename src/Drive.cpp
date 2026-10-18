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
void Drive::handlePacket(t_espnow_data packet)
{
	(void)packet;
	// TODO: Implementar
}
