#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "sensors.h"

// define pins here
// ex. const int pin = pin_num;

// arm stuff here

Gyro shoulder;
Gyro wrist;
Hand hand;
float elbow; /* potentiometer */

void init()
{
    // initialize library
    wiringPiSetupGpio();

    // initialize pin modes
}

void loop()
{
    while (running)
    {
        
    }
}

void main(int argc, char* argv[])
{

}
