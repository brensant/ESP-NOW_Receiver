#ifndef DRIVE_H
# define DRIVE_H

# include "Motor.h"
# include "comms.h"

class Drive {
  public:
	Drive(Motor left, Motor right);

	// Função(ões) para lidar com os pacotes ESP-NOW que chegam pelo controle remoto
	void handlePacket(t_espnow_data data);

  private:
	Motor m_motorLeft;
	Motor m_motorRight;
};

#endif // DRIVE_H
