#include <Servo.h>
#include <QueueArray.h>

#define BUF_SIZE NUM_FINGERS
#define AVG_THRESHOLD 10
#define NUM_FINGERS 5
#define NOISE_TOLERANCE 20
static int PWM_PINS[6] = {3,5,6,9,10,11}; // pwm pins avaliable for use
static int DIR_TOGGLE[6] = {33,35,37,39,41};
// easy names for array indices of the fingers
#define INDEX 0
#define MIDDLE 1
#define RING 2
#define PINKIE 3
#define THUMB 4
#define THUMB_SECONDARY 5
#define POT_NONE 0
#define POT_FULL 0
#define POT_MAP 0
// flag that indicates if we are calibrating the bend sensors
#define CALIBRATE_BUTTON 12 // button to activate calibrate mode
#define CALIBRATE_LED 13 // calibrate mode led indicator

#define SERVO_MIN 30
#define SERVO_MAX 150

int calibrate_mode = 0;

int weights[10] = {1.0f * 0.9f * 0.8f * 0.7f * 0.6f, 0.5f, 0.4f, 0.3f, 0.2f, 0.1};

// wrapper for all the pins necessary to control the fingers
typedef struct _Finger
{
  Servo servo;
  int sensor_pin;
  int low;
  int high;
  int last;
  bool invert;
  int avg;
  int history[AVG_THRESHOLD];
  // init array to be FULL from the start
} Finger;

Finger fingers[NUM_FINGERS]; // array of finger wrappers

int readPot(int pin){
  int value = analogRead(pin);
  return map(value, 0, 1024, 50, 100);
}

// fill all the values in the finger wrapper
void finger_setup(Finger* f, int sensor, int servo, int invert)
{
  f->invert = invert;
  f->sensor_pin = sensor;
  pinMode(sensor, INPUT);
  f->servo.attach(servo);
  if (f->invert)
  {
      f->servo.write(100);
  }
  f->low = analogRead(sensor);
  f->high = analogRead(sensor);

  Serial.print("PWM: ");
  Serial.println(servo);
}

// set min and max values of the bend sensors
void finger_calibrate(Finger* f)
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

  // TODO fill finger value (history array) with first read mapped value
}

// read and map bend sensor values
int finger_read(Finger* f)
{
  int val = analogRead(f->sensor_pin);
  int mapped = map(val, f->low, f->high, SERVO_MIN, SERVO_MAX);

  if (abs(mapped - f->last) > NOISE_TOLERANCE)
  {
    return mapped;
  }
  return f->last;
}

// write mapped values to the corresponding servo
void finger_write(Finger* f, int val)
{
  if (f->invert)
  {
      f->servo.write(SERVO_MAX-val);
  }
  else
  {
      f->servo.write(val);
  }
}

/*void finger_write_average(Finger* f)
{
    //avg = (history) dot product
    if (f->history_index < AVG_THRESHOLD-1)
    {
        // just write
    }
    else
    {
      // do avg algorithm
    }
}*/

void swap(int* array, int a, int b)
{
    int tmp = array[a];
    array[a] = array[b];
    array[b] = array[a];
}

int compute_average(Finger* )
{
    // add everything
    // divide by AVG_THRESHOLD
    // shift (call swap function)
}

// automatically read sensor and write to the servo
void finger_move(Finger* f)
{
  int val = finger_read(f);
  finger_write(f, val);
}

// Arduino setup function
void setup() {
    Serial.begin(9600);
    pinMode(CALIBRATE_BUTTON, INPUT_PULLUP);
    pinMode(CALIBRATE_LED, OUTPUT);

    for (int i=0; i<NUM_FINGERS;i++)
    {
      pinMode(DIR_TOGGLE[i], INPUT_PULLUP);
    }

    for (int i=0;i<NUM_FINGERS;i++){
      if (i == INDEX)
      {
        finger_setup(&fingers[i], i, PWM_PINS[i], 0);
      }
      else
      {
        finger_setup(&fingers[i], i, PWM_PINS[i], 1);
      }
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
      finger_calibrate(&fingers[i]);
    }
  }
  else
  {
    for (int i=0; i<NUM_FINGERS;i++)
    {
      fingers[i].invert = !digitalRead(DIR_TOGGLE[i]);
    }
    
    for (int i=0;i<NUM_FINGERS;i++)
    {
      finger_move(&fingers[i]);
      delay(1);
    }
  }
}
