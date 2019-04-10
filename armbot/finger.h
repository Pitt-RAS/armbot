#ifndef FINGER_H
#define FINGER_H

#include <stdint.h>

class Finger
{
public:
    Finger(uint8_t, uint8_t);
    ~Finger();

    void attach(uint8_t, uint8_t);
    void invert();

private:
    uint8_t servoPin;
    uint8_t sensorPin;
    uint8_t inverted;
};

#endif /* FINGER_H */