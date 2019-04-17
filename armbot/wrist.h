#ifndef WRIST_H
#define WRIST_H

#define PITCH_SERVO 5
#define YAW_SERVO 6
#define GYRO_MIN 0
#define GYRO_MAX 0

class Wrist
{
public:
    Wrist();
    ~Wrist();

    void attach();
    void poll();

private:
    int clk;
    int data;
    int pitch;
    int roll;
};

#endif /* WRIST_H */
