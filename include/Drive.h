#ifndef DRIVE_H
# define DRIVE_H

# include "Motor.h"
# include "comms.h"

class Drive {
  public:
	Drive(Motor left, Motor right);

	bool init(uint32_t frequency, uint8_t resolution = 8);

	void stop(); // Pára os dois motores. Chamar no failsafe.

	void handlePacket(const t_ctrl_pckt& packet);

	static constexpr int32_t MAX_SPEED = 255;

  private:
	static int32_t axisToSpeed(uint8_t raw); // 0..255 (centro 128) -> -255..255

	Motor m_motorLeft;
	Motor m_motorRight;
};

#endif // DRIVE_H
