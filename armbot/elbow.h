#ifndef ELBOW_H
#define ELBOW_H

#include <stdint.h>

class Elbow
{
public:
	Elbow(uint8_t a=0, uint8_t b=0, uint8_t c=0) :
		fwd_pin(a),
		rev_pin(b),
		sensor_pin(c),
		speed(0),
		dir(0),
		then(0),
		last_x(0),
		x(0),
		last_dx(0),
		dx(0),
		dx2(0)
	{}

	~Elbow() {}

	void attachMotor(uint8_t, uint8_t);
	void attachSensor(uint8_t);
	void setSpeed(uint16_t);
	void setDir(uint8_t);
	void poll();
	void drive();


private:
	uint8_t fwd_pin;
	uint8_t rev_pin;
	uint8_t sensor_pin;
	uint16_t speed;
	uint8_t dir;
	uint32_t then;
	float last_x;
	float x;
	float last_dx;
	float dx;
	float dx2;
};

#endif /* ELBOW_H */
