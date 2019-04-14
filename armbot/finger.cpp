#include "finger.h"
#include "util.h"
#include <Arduino.h>

#define SERVOMIN 200
#define SERVOMAX 600

void Finger::attach(uint8_t a, uint8_t b)
{
    sensorPin = a;
    servoPin = b;
    drv.begin();
    drv.setPWMFreq(60);
    drv = Adafruit_PWMServoDriver(&Wire, 0x40);
    servonum = 0;
}

void Finger::invert()
{
    inverted = !inverted;
}

void Finger::drive()
{
    Serial.println(servonum);
    for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
        drv.setPWM(servonum, 0, pulselen);
    }

    delay(500);
    for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
        drv.setPWM(servonum, 0, pulselen);
    }

    delay(500);

    //servonum ++;
    //if (servonum > 7) servonum = 0;
}

void Finger::setPulse(uint8_t n, double pulse)
{
    double pl = 1000000;
    pl /= 60;
    pl /= 1024; // 10 bits of resolution;
    pulse *= 1000000;
    pulse /= pl;
    Serial.println(pulse);
    drv.setPWM(n, 0, pulse);
}
