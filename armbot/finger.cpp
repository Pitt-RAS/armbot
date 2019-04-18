#include "finger.h"
#include "util.h"
#include "servomgr.h"
#include <Arduino.h>


// position
static int SENSOR_PINS[5] = {2, 3, 4, 5, 6};
static bool INVERT[5] = {false, false, false, false, false};
static bool SETUP[5] = {false, false, false, false, false};
static int SENSOR_LOWS[5];
static int SENSOR_HIGHS[5];

void Finger::attach(uint8_t sensor, uint8_t servo)
{
    sensor_pin = sensor;
    servo_num = servo;
    pinMode(sensor_pin, INPUT);
    sensor_min = analogRead(sensor_pin);
    sensor_max = analogRead(sensor_pin);
}

void Finger::calibrate()
{
    int val = analogRead(sensor_pin);
    Serial.print(servo_num);
    Serial.print(" ");
    Serial.println(val);
    if (val < sensor_min)
    {
        sensor_min = val;
        //SENSOR_LOWS[servonum] = val;
    }
    if (val > sensor_max)
    {
        sensor_max = val;
    //SENSOR_HIGHS[servonum] = val;
    }
}

void Finger::drive()
{
    
    int angle = map(analogRead(sensor_pin), sensor_min, sensor_max, 0, 180);

    if (!inverted)
    {
      ServoMgr::write(servo_num, angle);
    }
    else
    {
      ServoMgr::write(servo_num, 180 - angle);
    }
  
    // To-do: invert finger if invert == true and servo not already inverted
    //if (!SETUP[servonum]) {
        // To-do: invert finger if invert == true
    //    calibrate();
    //    SETUP[servonum] = true;
    //}
    //Serial.println(servonum);
    /*for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
       drv.setPWM(servonum, 0, pulselen);
    }

    delay(500);
    for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
        drv.setPWM(servonum, 0, pulselen);
    }
    */
    //int pulselen = read_sensor();
    //drv.setPWM(servonum, 0, pulselen);
    //delay(500);

    //servonum ++;
    //if (servonum >= NUMSERVOS) servonum = 0;
    //sensorPin = SENSOR_PINS[servonum];
    //invert = INVERT[servonum];
    //sensorLow = SENSOR_LOWS[servonum];
    //sensorHigh = SENSOR_HIGHS[servonum];
}

void Finger::invert()
{
  inverted = !inverted;
}
