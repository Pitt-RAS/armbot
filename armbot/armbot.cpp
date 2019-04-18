#include <Arduino.h>

#include "finger.h"
#include "wrist.h"
#include "elbow.h"
#include "servomgr.h"

//#define ECLIPSE

#define N_FINGERS 5
#define FINGER_ANALOG_OFFSET 33

Elbow elbow;
Wrist wrist;
Finger fingers[N_FINGERS];
int toInvert[5] = {1,1,1,0,0};

int mode = 0;

void armbot_setup()
{
    Serial.begin(9600);

    Wire.setSDA(18);
    Wire.setSCL(19);
    Wire.begin();

    ServoMgr::attach();

    elbow.attach();
    wrist.attach();
    
    int i;
    for (i=0; i<N_FINGERS; i++)
    {
        fingers[i].attach(FINGER_ANALOG_OFFSET + i, i);
        if (toInvert[i])
        {
          fingers[i].invert();
        }
    }

    pinMode(23, INPUT);   
}

void armbot_loop()
{
    if (!digitalRead(23))
    {
      Serial.println("YES");
      mode = !mode;
      delay(1000);
    }

    if (!mode)
    {
        int i;
        for (i=0; i<N_FINGERS; i++)
        {
            fingers[i].drive();
        }
        //elbow.drive();
        //wrist.drive();
        //wrist.test(); 
    }
    else if (mode)
    {
        int i;
    for (i=0; i<N_FINGERS; i++)
    {
        fingers[i].calibrate();
    }
    }
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
