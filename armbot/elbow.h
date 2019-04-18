#ifndef ELBOW_H
#define ELBOW_H

#include <stdint.h>

#define FORWARD_PIN 0
#define REVERSE_PIN 0
#define SENSOR_PIN 0
#define FEEDBACK_PIN 0


class Elbow
{
public:
	Elbow() {}

	~Elbow() {}

	void attach();
	void poll();
	void drive();


private:

};

#endif /* ELBOW_H */
