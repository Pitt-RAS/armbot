#pragma once

#include <stdint.h>

#define SERIAL_PORT "/dev/ttyACM0"

typedef struct _Packet
{
    // all values 0-255
    // gyros have x,y,z rotation and acceleration
    uint8_t gyro1[6];
    uint8_t gyro2[6];
    // elbow mounted potentiometer
    uint8_t pot;
    // 5 fingers
    uint8_t hand[5];
    int fd;
} Packet;

int open_serial_port();
int packet_get_next(Packet*);
