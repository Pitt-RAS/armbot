#include "servomgr.h"

Adafruit_PWMServoDriver ServoMgr::drv = Adafruit_PWMServoDriver();

void ServoMgr::attach()
{
    drv = Adafruit_PWMServoDriver(&Wire, 0x40);
    drv.begin();
    drv.setPWMFreq(60);
}

void ServoMgr::write(int index, int angle)
{
    int pulse = map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
    drv.setPWM(index, 0, pulse);
}