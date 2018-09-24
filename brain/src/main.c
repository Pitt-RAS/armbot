#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef TESTING
#include <wiringPi.h>
#endif
#include "sensors.h"
#include "link.h"

// define pins here
// ex. const int pin = pin_num;

bool running;

// sensors
Gyro shoulder;
Gyro wrist;
Hand hand;
float elbow; /* potentiometer */

// communications stuff
Packet packet;

void setup()
{
    #ifndef TESTING
    /* initialize library and pin modes */
    //wiringPiSetupGpio();
    #endif
}

void loop()
{
    // get the next packet from the stream
    packet_get_next(&packet);

    // parse data values from packet
    gyro_parse_packet(&wrist, &packet, 0);
    gyro_parse_packet(&shoulder, &packet, 1);
    hand_parse_packet(&hand, &packet);
    elbow = pot_parse_packet(&packet);

    // calculate rotations with the following procedure
    // add elbow angle to wrist angle
    // subtract shoulder angles from wrist angles

    // move motors

}

int main(int argc, char* argv[])
{
    setup();
    while (running)
    {
        loop();
    }
}
