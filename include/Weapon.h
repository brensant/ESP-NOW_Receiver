#ifndef WEAPON_H
# define WEAPON_H

# include "Motor.h"
# include "comms.h"

# include <cstdint>

class Weapon {
  public:
	explicit Weapon(Motor motor);

	bool init(uint32_t frequency, uint8_t resolution = 8);
	void stop();
	void handlePacket(const t_ctrl_pckt &packet);
	bool isActive() const;

	static constexpr uint8_t POWER = 255;
	static constexpr uint8_t STABLE_COUNT = 2; // pacotes consecutivos iguais para aceitar a mudança

  private:
	Motor    m_motor;
	bool     m_isActive;
	bool     m_stableState; // último estado aceito do botão
	bool     m_candidate;   // estado candidato (ainda não estável)
	uint8_t  m_candidateCount;
	uint16_t m_lastPacketId;
	bool     m_hasLastId;
};

#endif // WEAPON_H
