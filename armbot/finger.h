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
    void setPulse(uint8_t, double);
    int read_sensor();
    void drive();
    void calibrate();

private:
    uint8_t servoPin;
    uint8_t sensorPin;
    uint8_t inverted;
    uint8_t servonum;
    bool invert;
    int sensorLow;
    int sensorHigh;
    Adafruit_PWMServoDriver drv = Adafruit_PWMServoDriver();
};

#endif /* FINGER_H */
