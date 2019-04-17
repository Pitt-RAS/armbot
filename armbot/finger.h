#ifndef FINGER_H
#define FINGER_H

#include <stdint.h>
#include <Adafruit_PWMServoDriver.h>

#define DRIVER_ADDR 0x40

class Finger
{
public:
    Finger(uint8_t a=0, uint8_t b=0) : servoPin(a), sensorPin(b), inverted(0) {}
    ~Finger() {}

    void attach(uint8_t, uint8_t);
    void drive();
    void calibrate();
    void invert();

private:
    uint8_t servo_num;
    uint8_t sensor_pin;
    int inverted;
    int calibrate;
    int sensor_min;
    int sensor_max;
    Adafruit_PWMServoDriver drv = Adafruit_PWMServoDriver();
};

#endif /* FINGER_H */
