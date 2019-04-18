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
    //Serial.print("write ");
    //Serial.print(index);
    //Serial.print(" ");
    //Serial.print(angle);
    int pulse = map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
    //Serial.print(" ");
    //Serial.println(pulse);
    //Serial.println("\n");
    /*for (uint16_t pulselen = SERVO_MIN; pulselen < SERVO_MAX; pulselen++) {
      drv.setPWM(1, 0, pulselen);
    }*/
    drv.setPWM(index, 0, pulse);
    //drv.setPWM(index, 1024, 3072);
}
