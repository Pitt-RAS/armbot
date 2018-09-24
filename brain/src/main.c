#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <wiringPi.h>
#include "sensors.h"
#include "link.h"

// define pins here
// ex. const int pin = pin_num;

// arm stuff here
bool running;

Gyro shoulder;
Gyro wrist;
Hand hand;
float elbow; /* potentiometer */

// communications stuff
Packet packet;

void setup()
{
    /* initialize library and pin modes */
    //wiringPiSetupGpio();

}

void loop()
{
    packet_get_next(&packet);
    gyro_parse_packet(&wrist, &packet, 0);
    gyro_parse_packet(&shoulder, &packet, 1);
    hand_parse_packet(&hand, &packet);
    elbow = pot_parse_packet(&packet);
}

int main(int argc, char* argv[])
{
    setup();
    while (running)
    {
        loop();
    }
}
