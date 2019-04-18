#ifndef SERVOMGR_H
#define SERVOMGR_H

#define DRIVER_ADDR 0X40
#define SERVO_MIN 250
#define SERVO_MAX 540

#include <Adafruit_PWMServoDriver.h>

class ServoMgr
{
public:

    static void attach();
    static void write(int, int);

private:
    static Adafruit_PWMServoDriver drv;
};

#endif /* SERVOMGR_H */
