#include "Drive.h"

/*********************************** TYPES ************************************/

/********************************* LIFECYCLE **********************************/

Drive::Drive(Motor motorLeft, Motor motorRight)
  : m_motorLeft(motorLeft)
  , m_motorRight(motorRight)
{
}

Drive::~Drive()
{
}

/************************** STATIC MEMBER FUNCTIONS ***************************/

/************************ NON-STATIC MEMBER FUNCTIONS *************************/

void Drive::handlePacket(t_espnow_data packet)
{
	// TODO: Implementar
}

/* OPERATORS */

/****************************** HELPER FUNCTIONS ******************************/

/* OPERATORS */
