#include <Servo.h>
#define BUF_SIZE NUM_FINGERS

#define NUM_FINGERS 2
#define NOISE_TOLERANCE 20
static int PWM_PINS[6] = {3,5,6,9,10,11};

typedef struct _FINGER
{
  Servo servo;
  int sensor_pin;
  int low;
  int high;
  int last;
} FINGER;

// fingers
#define INDEX 0
#define MIDDLE 1
#define RING 2
#define PINKIE 3
#define THUMB 4
#define THUMB_SECONDARY 5

// potentiomenter
// todo fill values
#define POT_NONE 0
#define POT_FULL 0
#define POT_MAP 0

int calibrate_mode = 0;
#define CALIBRATE_BUTTON 12
#define CALIBRATE_LED 13

FINGER tmp_fingers[NUM_FINGERS];

int readPot(int pin){
  int value = analogRead(pin);
  return map(value, 0, 1024, 0, 180);
}

void finger_setup(FINGER* f, int sensor, int servo)
{
  f->sensor_pin = sensor;
  pinMode(sensor, INPUT);
  f->servo.attach(servo);
  f->low = analogRead(sensor);
  f->high = analogRead(sensor);

  Serial.print("PWM: ");
  Serial.println(f->servo.attached());
}

void finger_calibrate(FINGER* f)
{
  int val = analogRead(f->sensor_pin);
  Serial.print("val :");
  Serial.println(val);
  if (val < f->low)
  {
    f->low = val;
  }
  if (val > f->high)
  {
    f->high = val;
  }
}

int finger_read(FINGER* f)
{
  int val = analogRead(f->sensor_pin);
  int mapped = map(val, f->low, f->high, 0, 180);

  if (abs(mapped - f->last) > NOISE_TOLERANCE)
  {
    return mapped;
  }
  return f->last;
}

void finger_write(FINGER* f, int val)
{
  f->servo.write(val);
}

void finger_move(FINGER* f)
{
  int val = finger_read(f);
  finger_write(f, val);
}

void setup() {
    Serial.begin(9600);
    pinMode(CALIBRATE_BUTTON, INPUT_PULLUP);
    pinMode(CALIBRATE_LED, OUTPUT);
    
    for (int i=0;i<NUM_FINGERS;i++){
      finger_setup(&tmp_fingers[i], i, PWM_PINS[i]);
    }
    
}

void loop() {
  int val = digitalRead(CALIBRATE_BUTTON);
  if (val == LOW)
  {
    calibrate_mode = !calibrate_mode;
    digitalWrite(CALIBRATE_LED, HIGH);
    delay(1000);
    digitalWrite(CALIBRATE_LED, calibrate_mode);
  }
  if (calibrate_mode)
  {
    digitalWrite(CALIBRATE_LED, LOW);
    delay(50);
    digitalWrite(CALIBRATE_LED, HIGH);
    delay(50);

    for (int i=0; i<NUM_FINGERS; i++)
    {
      finger_calibrate(&tmp_fingers[i]);    
    }
  }
  else
  {
    for (int i=0;i<NUM_FINGERS;i++){
      finger_move(&tmp_fingers[i]);
      delay(1);    
    }  
  }
}
