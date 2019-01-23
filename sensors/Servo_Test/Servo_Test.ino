#include <Servo.h>
#define BUF_SIZE NUM_FINGERS

#define NUM_FINGERS 3
#define NOISE_TOLERANCE 20
static int PWM_PINS[6] = {3,5,6,9,10,11}; // pwm pins avaliable for use

// wrapper for all the pins necessary to control the fingers
typedef struct _FINGER
{
  Servo servo;
  int sensor_pin;
  int low;
  int high;
  int last;
} FINGER;

// easy names for array indices of the fingers
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

// flag that indicates if we are calibrating the bend sensors
int calibrate_mode = 0;
#define CALIBRATE_BUTTON 12 // button to activate calibrate mode
#define CALIBRATE_LED 13 // calibrate mode led indicator

FINGER tmp_fingers[NUM_FINGERS]; // array of finger wrappers

int readPot(int pin){
  int value = analogRead(pin);
  return map(value, 0, 1024, 0, 180);
}

// fill all the values in the finger wrapper
void finger_setup(FINGER* f, int sensor, int servo)
{
  f->sensor_pin = sensor;
  pinMode(sensor, INPUT);
  f->servo.attach(servo);
  f->low = analogRead(sensor);
  f->high = analogRead(sensor);

  Serial.print("PWM: ");
  Serial.println(servo);
}

// set min and max values of the bend sensors 
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

// read and map bend sensor values
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

// write mapped values to the corresponding servo
void finger_write(FINGER* f, int val)
{
  f->servo.write(val);
}

// automatically read sensor and write to the servo
void finger_move(FINGER* f)
{
  int val = finger_read(f);
  finger_write(f, val);
}

// Arduino setup function
void setup() {
    Serial.begin(9600);
    pinMode(CALIBRATE_BUTTON, INPUT_PULLUP);
    pinMode(CALIBRATE_LED, OUTPUT);
    
    for (int i=0;i<NUM_FINGERS;i++){
      finger_setup(&tmp_fingers[i], i, PWM_PINS[i]);
    }
    
}

// Arduino loop function
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
