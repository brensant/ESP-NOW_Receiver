#include "Robot.h"

/********************************* LIFECYCLE **********************************/

Robot::Robot(Drive &drive, Weapon* weapon)
  : m_drive(drive)
  , m_weapon(weapon)
{
}

/************************ NON-STATIC MEMBER FUNCTIONS *************************/

bool Robot::init(uint32_t frequency, uint8_t resolution)
{
	bool isDriveOk = m_drive.init(frequency, resolution);
	bool isWeaponOk = m_weapon ? m_weapon->init(frequency, resolution) : true;

	return (isDriveOk && isWeaponOk);
}

void Robot::stop()
{
	m_drive.stop();

	if (m_weapon)
		m_weapon->stop();
}

void Robot::handlePacket(const t_ctrl_pckt &packet)
{
	m_drive.handlePacket(packet);

	if (m_weapon)
		m_weapon->handlePacket(packet);
}
