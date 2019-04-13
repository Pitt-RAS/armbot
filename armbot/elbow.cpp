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
	/*// integrate
	uint32_t now = millis();
	float delta = now - then;
	then = now;
	uint16_t val = analogRead(sensor_pin);
	//x = normalize(val);
	x = val;
	dx = (x - last_x) / (delta/1.0f);
	dx2 = (dx - last_dx) / (delta/1.0f);
	last_x = x;
	last_dx = dx;

	angle += dx;
	if (angle > 1023)
	{
		angle = 0;
	}

	Serial.print("val: ");
	Serial.print(val);
	Serial.print("\tangle: ");
	Serial.print(angle);
	Serial.print("\tx: ");
	Serial.print(x);
	Serial.print("\tdx: ");
	Serial.print(dx);
	Serial.print("\tdx2: ");
	Serial.print(dx2);
	Serial.print("\tspeed: ");
	Serial.print(dx);
	Serial.println();

	if (dx <= 0)
	{
		dir = 0;
	}
	else if (dx > 1)
	{
		dir = 1;
	}

	//speed = abs(1023 * dx);					// calculate speed
	speed = 600;

	if (angle == val || dx == 0)
	{
		speed = 0;
	}*/

	int val = analogRead(sensor_pin);
	int angle = map(val, 0, 1023, 0, 270);
	val = analogRead(1);
	int feedback = map(val, 0, 1023, 0, 270);

	dir = ((angle - feedback) / abs(angle - feedback));
	//speed = 1023.0f / (1 + exp( (1.0f/27.0f) * (-1 * ((angle - feedback) - pow(27,3.0f/2.0f) ))));
	speed = (float)abs(angle - feedback) / (270.0f) * 256.0f;
	if (speed < (int)(0.1 * 256))
	{
		speed = 0;
	}

	Serial.print("angle: ");
	Serial.print(angle);
	Serial.print("\tfeedback: ");
	Serial.print(feedback);
	Serial.print("\tdir: ");
	Serial.print(dir);
	Serial.print("\tspeed: ");
	Serial.print(speed);
	Serial.println();
}

void Elbow::drive()
{
	if (dir == 1)
	{
		analogWrite(rev_pin, 0);
		analogWrite(fwd_pin, speed);
	}
	else if (dir == -1)
	{
		analogWrite(fwd_pin, 0);
		analogWrite(rev_pin, speed);
	}
}
