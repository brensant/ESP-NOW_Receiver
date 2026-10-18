#ifndef MOTOR_H
# define MOTOR_H

# include <cstdint>

# define MAX_DUTY 255

class Motor {
  public:
	Motor(uint8_t en, uint8_t in1, uint8_t in2, uint8_t pwmPin);

	bool init(uint32_t frequency, uint8_t resolution = 8);

	void forward(uint8_t speed);
	void backward(uint8_t speed);
	void setSpeed(int16_t speed);
	void stop();

  private:
	void writePwm(uint8_t speed);

	const uint8_t  m_en;
	const uint8_t  m_in1;
	const uint8_t  m_in2;
	const uint8_t  m_pwmPin;
	const uint32_t m_maxDuty;
};

#endif // MOTOR_H
