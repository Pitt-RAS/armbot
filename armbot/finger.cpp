#include "finger.h"
#include <Arduino.h>

Finger::Finger(uint8_t a=0, uint8_t b=0): 
    sensorPin(a), 
    servoPin(b), 
    inverted(0)
{

}

Finger::~Finger()
{

}

void Finger::attach(uint8_t a, uint8_t b)
{
    sensorPin = a;
    servoPin = b;
}

void Finger::invert()
{
    inverted = !inverted;
}
