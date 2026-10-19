#ifndef ROBOT_H
# define ROBOT_H

# include "Drive.h"
# include "Weapon.h"
# include "comms.h"

class Robot {
  public:
	// `weapon` é opcional: nullptr = robô sem arma (sumô).
	// Drive e Weapon não são copiados: precisam viver mais que o Robot.
	explicit Robot(Drive& drive, Weapon* weapon = nullptr);

	bool init(uint32_t frequency, uint8_t resolution = 8);
	void stop(); // failsafe: para rodas e arma
	void handlePacket(const t_ctrl_pckt& packet);

  private:
	Drive  &m_drive;
	Weapon *m_weapon;
};

#endif // ROBOT_H
