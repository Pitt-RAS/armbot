#include "elbow.h"
#include "util.h"
#include <Arduino.h>

void Elbow::attachMotor(uint8_t a, uint8_t b)
{
	fwd_pin = a;
	rev_pin = b;
}

void Elbow::attachSensor(uint8_t a)
{
	sensor_pin = a;
}

void Elbow::setSpeed(uint16_t a)
{
	speed = a;
}

void Elbow::setDir(uint8_t a)
{
	dir = a;
}

void Elbow::poll()
{
	// integrate
	uint32_t now = millis();
	float delta = now - then;
	then = now;
	uint16_t val = analogRead(sensor_pin);
	x = normalize(val);
	dx = (x - last_x) / delta;
	dx2 = (dx - last_dx) / delta;
	last_x = x;
	last_dx = dx;

	if (dx <= 0)
	{
		dir = 0;
	}
	else if (dx > 1)
	{
		dir = 1;
	}

	speed = 1023 * dx;					// calculate speed
	speed = max(0, min(speed, 1023)); 	// clamp values
}

void Elbow::drive()
{
	if (!dir)
	{
		analogWrite(rev_pin, 0);
		analogWrite(fwd_pin, speed);
	}
	else
	{
		analogWrite(fwd_pin, 0);
		analogWrite(rev_pin, speed);
	}
}
