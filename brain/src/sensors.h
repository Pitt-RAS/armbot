#pragma once

#include "link.h"

typedef struct _Gyro
{
    float x;
    float y;
    float z;
} Gyro;

typedef struct _Hand
{
    float index;
    float middle;
    float ring;
    float pinkie;
    float thumb;
} Hand;

void gyro_parse_packet(Gyro*, Packet*);
void hand_parse_packet(Hand*, Packet*);
