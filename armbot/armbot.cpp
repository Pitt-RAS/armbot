#include <Arduino.h>

#include "finger.h"
#include "wrist.h"
#include "elbow.h"

#define ECLIPSE

#define N_FINGERS 5

Elbow elbow;
Wrist wrist;
Finger fingers[N_FINGERS];

void armbot_setup()
{
    Serial.begin(9600);
    elbow.attachMotor(10, 11);
    elbow.attachSensor(0);
}

void armbot_loop()
{
	elbow.poll();
	elbow.drive();
}

#ifdef ECLIPSE

void setup()
{
	armbot_setup();
}

void loop()
{
	armbot_loop();
}

#endif /* ECLIPSE */
