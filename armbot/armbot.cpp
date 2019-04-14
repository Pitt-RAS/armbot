#include <Arduino.h>

#include "finger.h"
#include "wrist.h"
#include "elbow.h"

//#define ECLIPSE

#define N_FINGERS 5

Elbow elbow;
Wrist wrist;
Finger finger;
Finger fingers[N_FINGERS];

void armbot_setup()
{
    Serial.begin(9600);
    Wire.setSDA(18);
    Wire.setSCL(19);
    Wire.begin();
    elbow.attachMotor(10, 11);
    elbow.attachSensor(0);
    wrist.attach(19,18);
    finger.attach(1,1);
}

void armbot_loop()
{
	//elbow.poll();
	//elbow.drive();
  wrist.poll();
  finger.drive();
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
