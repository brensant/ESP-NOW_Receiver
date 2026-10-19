#include "Weapon.h"

/********************************* LIFECYCLE **********************************/

Weapon::Weapon(Motor motor)
  : m_motor(motor)
  , m_isActive(false)
  , m_stableState(true) // exige soltar o botão antes do primeiro clique
  , m_candidate(true)
  , m_candidateCount(0)
  , m_lastPacketId(0)
  , m_hasLastId(false)
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
	m_stableState = true; // após failsafe, exige soltar antes de aceitar clique
	m_candidate = true;
	m_candidateCount = 0;
	m_hasLastId = false;
}

void Weapon::handlePacket(const t_ctrl_pckt& packet)
{
	// O loop() relê o mesmo pacote várias vezes: só processa pacotes novos.
	if (m_hasLastId && packet.packetId == m_lastPacketId)
		return;

	m_lastPacketId = packet.packetId;
	m_hasLastId = true;

	bool pressed = (packet.button != 0);

	if (pressed != m_candidate) {
		m_candidate = pressed;
		m_candidateCount = 1;
	} else if (m_candidateCount < STABLE_COUNT) {
		m_candidateCount++;
	}

	if (m_candidateCount < STABLE_COUNT || m_candidate == m_stableState)
		return;

	// Mudança de estado confirmada.
	m_stableState = m_candidate;

	if (m_stableState) { // borda de subida: um clique
		m_isActive = !m_isActive;
		if (m_isActive)
			m_motor.forward(POWER);
		else
			m_motor.stop();
	}
}

bool Weapon::isActive() const
{
	return (m_isActive);
}
