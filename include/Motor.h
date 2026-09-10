#ifndef MOTOR_H
# define MOTOR_H

# include <stdint.h>

class Motor {
  public:
	Motor(uint8_t en, uint8_t in1, uint8_t in2, uint8_t pwmChannel);

	void begin(uint32_t frequency, uint8_t resolution = 8);
	void forward(uint8_t speed);
	void backward(uint8_t speed);
	void stop();

  private:
	uint8_t m_en;
	uint8_t m_in1;
	uint8_t m_in2;
	uint8_t m_pwmChannel;
};

#endif // MOTOR_H
