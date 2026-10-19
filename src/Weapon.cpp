#include "Weapon.h"

/********************************* LIFECYCLE **********************************/

Weapon::Weapon(Motor motor)
  : m_motor(motor)
  , m_isActive(false)
  , m_wasPressed(true)
{
}

/************************ NON-STATIC MEMBER FUNCTIONS *************************/

bool Weapon::init(uint32_t frequency, uint8_t resolution)
{
	if (!m_motor.init(frequency, resolution))
		return (false);

	stop();
	return (true);
}

void Weapon::stop()
{
	m_motor.stop();
	m_isActive = false;
	m_wasPressed = true; // exige soltar o botão antes de aceitar um novo clique
}

void Weapon::handlePacket(const t_ctrl_pckt &packet)
{
	bool isPressed = packet.flags.isWeaponEnabled;

	if (isPressed && !m_wasPressed) {
		m_isActive = !m_isActive;

		if (m_isActive)
			m_motor.forward(POWER);
		else
			m_motor.stop();
	}

	m_wasPressed = isPressed;
}

bool Weapon::isActive() const
{
	return (m_isActive);
}
