#include "finger.h"
#include "util.h"
#include <Arduino.h>


// position
#define SERVOMIN 200
#define SERVOMAX 600
#define NUMSERVOS 5
static int SENSOR_PINS[5] = {2, 3, 4, 5, 6};
static bool INVERT[5] = {false, false, false, false, false};
static bool SETUP[5] = {false, false, false, false, false};
static int SENSOR_LOWS[5];
static int SENSOR_HIGHS[5];

void Finger::attach(uint8_t a, uint8_t b)
{
    sensorPin = a;
    pinMode(sensorPin, INPUT);
    servoPin = b;
    drv.begin();
    drv.setPWMFreq(60); // Analog servos run at ~60 Hz updates
    drv = Adafruit_PWMServoDriver(&Wire, 0x40);
    servonum = 0; // which port they are assoc w/0-6
    invert = INVERT[servonum];
    int val = analogRead(sensorPin);
    for (int i = 0; i < NUMSERVOS; i++) {
      SENSOR_LOWS[i] = val;
      SENSOR_HIGHS[i] = val;
    }
}

void Finger::calibrate()
{
  int val = analogRead(sensorPin);
  if (val < sensorLow)
  {
    sensorLow = val;
    SENSOR_LOWS[servonum] = val;
  }
  if (val > sensorHigh)
  {
    sensorHigh = val;
    SENSOR_HIGHS[servonum] = val;
  }
}

int Finger::read_sensor()
{
  int val = analogRead(sensorPin);
  return map(val, sensorLow, sensorHigh, SERVOMIN, SERVOMAX);
}

void Finger::drive()
{
    // To-do: invert finger if invert == true and servo not already inverted
    if (!SETUP[servonum]) {
        // To-do: invert finger if invert == true
        calibrate();
        SETUP[servonum] = true;
    }
    Serial.println(servonum);
    /*for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
       drv.setPWM(servonum, 0, pulselen);
    }

    delay(500);
    for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
        drv.setPWM(servonum, 0, pulselen);
    }
    */
    int pulselen = read_sensor();
    drv.setPWM(servonum, 0, pulselen);
    delay(500);

    servonum ++;
    if (servonum >= NUMSERVOS) servonum = 0;
    sensorPin = SENSOR_PINS[servonum];
    //invert = INVERT[servonum];
    sensorLow = SENSOR_LOWS[servonum];
    sensorHigh = SENSOR_HIGHS[servonum];
}
