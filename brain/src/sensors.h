#pragma once

#include "link.h"

typedef struct _Gyro
{
    float ax;
    float ay;
    float az;
    float rx;
    float ry;
    float rz;
} Gyro;

typedef struct _Hand
{
    float index;
    float middle;
    float ring;
    float pinkie;
    float thumb;
} Hand;

void gyro_parse_packet(Gyro*, Packet*, int);
void hand_parse_packet(Hand*, Packet*);
float pot_parse_packet(Packet*);
