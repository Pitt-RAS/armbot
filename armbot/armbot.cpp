#include <Arduino.h>

#include "finger.h"
#include "wrist.h"
#include "elbow.h"

//#define ECLIPSE

#define N_FINGERS 5
#define FINGER_ANALOG_OFFSET 0

Elbow elbow;
Wrist wrist;
Finger fingers[N_FINGERS];

void armbot_setup()
{
    Serial.begin(9600);

    Wire.setSDA(18);
    Wire.setSCL(19);
    Wire.begin();

    elbow.attach();
    wrist.attach();
    
    int i;
    for (i=0; i<N_FINGERS; i++)
    {
        fingers[i].attach(FINGER_ANALOG_OFFSET + i, i);
    }
    
}

void armbot_loop()
{
    elbow.drive();
    wrist.drive();
  
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
