#include "finger.h"
#include <Arduino.h>

void Finger::attach(uint8_t a, uint8_t b)
{
    sensorPin = a;
    servoPin = b;
}

void Finger::invert()
{
    inverted = !inverted;
}
