#ifndef WEAPON_HPP
# define WEAPON_HPP

# include "Motor.h"
# include "comms.h"

class Weapon {
  public:
	explicit Weapon(Motor motor);

	bool init(uint32_t frequency, uint8_t resolution = 8);

	// Desliga a arma e zera o estado do toggle. Chamar no failsafe.
	void stop();

	// Alterna liga/desliga na borda de subida do botão.
	void handlePacket(const t_ctrl_pckt &packet);

	bool isActive() const;

	static constexpr uint8_t POWER = 255;

  private:
	Motor m_motor;
	bool  m_isActive;
	bool  m_wasPressed;
};

#endif // WEAPON_H
