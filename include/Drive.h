#ifndef DRIVE_H
# define DRIVE_H

# include "Motor.h"
# include "comms.h"

class Drive {
  public:
	Drive(Motor left, Motor right);

	bool init(uint32_t frequency, uint8_t resolution = 8);

	void stop(); // Para os dois motores. Chamar no failsafe.

	void handlePacket(t_espnow_data data);

  private:
	Motor m_motorLeft;
	Motor m_motorRight;
};

#endif // DRIVE_H
