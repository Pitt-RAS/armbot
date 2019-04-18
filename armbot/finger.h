#ifndef FINGER_H
#define FINGER_H

#include <stdint.h>
#include <Adafruit_PWMServoDriver.h>

class Finger
{
public:
    Finger() {
      inverted = 0;
    }
    ~Finger() {}

    void attach(uint8_t, uint8_t);
    void drive();
    void calibrate();
    void invert();

private:
    uint8_t servo_num;
    uint8_t sensor_pin;
    int inverted;
    int calibrate_mode;
    int sensor_min;
    int sensor_max;
    Adafruit_PWMServoDriver drv = Adafruit_PWMServoDriver();
};

#endif /* FINGER_H */
