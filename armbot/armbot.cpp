#include <Arduino.h>

void armbot_setup()
{
    Serial.begin(9600);
}

void armbot_loop()
{
    Serial.println("hello world");
}
