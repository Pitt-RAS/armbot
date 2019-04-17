#ifndef SERVOMGR_H
#define SERVOMGR_H

#define DRIVER_ADDR 0X40
#define SERVO_MIN 200
#define SERVO_MAX 600

#include <Adafruit_PWMServoDriver.h>

class ServoMgr
{
public:

    static void attach();
    static void write(int, int);

private:
    static Adafruit_PWMservoDriver drv;
};

#endif /* SERVOMGR_H */