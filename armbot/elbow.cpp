#include "elbow.h"
#include "util.h"
#include <Arduino.h>

void Elbow::attach()
{
	pinMode(SENSOR_PIN, INPUT);
	pinMode(FEEDBACK_PIN, INPUT);
	pinMode(FORWARD_PIN, OUTPUT);
	pinMode(REVERSE_PIN, OUTPUT);
}

void Elbow::drive()
{
	int target = map(analogRead(SENSOR_PIN), 0, 1024, 0, 180);
	int current = map(analogRead(FEEDBACK_PIN), 0, 1024, 0, 180);

	int dir = (current - target) / abs(current - target);
	int speed = 200;

	if (dir == 1)
	{
		analogWrite(REVERSE_PIN, 0);
		analogWrite(FORWARD_PIN, speed);
	}
	else if (dir == -1)
	{
		analogWrite(FORWARD_PIN, 0);
		analogWrite(REVERSE_PIN, speed);
	}
}
