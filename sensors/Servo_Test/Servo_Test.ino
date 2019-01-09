#include <Servo.h>
#define BUF_SIZE 6

#define VCC 5
#define TOLERANCE 10

#define CALIBRATE_BUTTON 7
#define CALIBRATE_LED 8

// bend sensors
#define BEND_STRAIGHT 880
#define BEND_FLEX 580
#define R_DIV 10000

// fingers
#define INDEX_PIN 0
#define MIDDLE_PIN 1
#define RING_PIN 2
#define PINKIE_PIN 0
#define THUMB_PIN 1
#define WRIST_PIN 8
#define POT_PIN 12

//Servos
#define INDEX_FINGER 3
#define MIDDLE_FINGER 5
#define RING_FINGER 6
#define PINKY_FINGER 9
#define THUMB_FINGER 10
#define THUMB_B_FINGER 11

// potentiomenter
// todo fill values
#define POT_NONE 0
#define POT_FULL 0
#define POT_MAP 0

int buffer[BUF_SIZE];
 Servo pinky;
 Servo ring;
 Servo middle;
 Servo index;
 Servo thumb;
 Servo thumb_b;
 Servo fingers[]={pinky,ring,middle,index,thumb,thumb_b};
 int pins[]={PINKY_FINGER,RING_FINGER,MIDDLE_FINGER,INDEX_FINGER,THUMB_FINGER,THUMB_B_FINGER};
 int inputs[]={PINKIE_PIN,RING_PIN,MIDDLE_PIN,INDEX_PIN,THUMB_PIN,WRIST_PIN};
boolean calibrate = false;

void setup() {
    Serial.begin(9600);
    pinMode(INDEX_PIN, INPUT);
    pinMode(MIDDLE_PIN, INPUT);
    pinMode(RING_PIN, INPUT);
    pinMode(PINKIE_PIN, INPUT);
    pinMode(THUMB_PIN, INPUT);
    pinMode(WRIST_PIN, INPUT);
    pinMode(POT_PIN, INPUT);
    pinMode(CALIBRATE_BUTTON, INPUT);
    pinMode(CALIBRATE_LED, OUTPUT);
    for (int i=0;i<6;i++){
      fingers[i].attach(pins[i]);
    }
    
}

int readFlexSensor(int pin)
{
    int value = analogRead(pin);
    Serial.println(value);
    float flexV = value * VCC / 1023.0;
    float flexR = R_DIV * (VCC / flexV - 1.0);
    return map(flexR, BEND_STRAIGHT, BEND_FLEX, 0, 180);
}
int readPot(int pin){
  int value = analogRead(pin);
  return map(value, 0, 1024, 0, 180);
}

void loop() {
  int val = digitalRead(CALIBRATE_BUTTON);
  digitalWrite(CALIBRATE_LED, val);

  if (calibrate)
  {
    digitalWrite(CALIBRATE_LED, HIGH);
  }
  
  for (int i=0;i<6;i++){
    int current=fingers[i].read();
    int newVal=readFlexSensor(inputs[i]);
    if(abs(current-newVal)>TOLERANCE){
      fingers[i].write(newVal);
    }
    //Serial.print(i+"-");
    //Serial.print(newVal);
    //Serial.print(" - ");
    //Serial.println(analogRead(pins[i]));
    
  }
   
 
    delay(100);
}
