#include <Servo.h>

#define BUF_SIZE NUM_FINGERS
#define AVG_THRESHOLD 10 // the number of data points being considered (weighted avg.)
#define NUM_FINGERS 5

#define NOISE_TOLERANCE 20
static int PWM_PINS[6] = {3,5,6,9,10,11}; // pwm pins avaliable for use
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

int calibrate_mode = 0;

//int weights[AVG_THRESHOLD] = {1.0f , 0.9f , 0.8f , 0.7f , 0.6f, 0.5f, 0.4f, 0.3f, 0.2f, 0.1};
float weights[AVG_THRESHOLD] = {1.0f , 1.0f , 1.0f , 1.0f , 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f}

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
  return map(value, 0, 1024, 0, 180);
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
      f->servo.write(180);
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

  // fill finger value (history array) with first read mapped value
  int avg = (f->low + f->high)/2;
  for (int i = 0; i < AVG_THRESHOLD; i ++)
    f->history[i] = avg;
}

// read and map bend sensor values
int finger_read(Finger* f)
{
  int val = analogRead(f->sensor_pin);
  int mapped = map(val, f->low, f->high, 0, 180);
  //Serial.print(mapped);
  //Serial.print("\t");
  return finger_write_average(f, mapped);
  /*if (abs(mapped - f->last) > NOISE_TOLERANCE)
  {
    return mapped;
  }
  return f->last;
  */
}

// write mapped values to the corresponding servo
void finger_write(Finger* f, int val)
{
  if (f->invert)
  {
      f->servo.write(180-val);
  }
  else
  {
      f->servo.write(val);
  }
}

int finger_write_average(Finger* f, int val)
{
    int finger_average = compute_average(f, val);
    f->servo.write(finger_average);
    Serial.print(finger_average);
    Serial.print("\n");
    return finger_average;
}

void swap(int* array, int a, int b)
{
    int tmp = array[a];
    array[a] = array[b];
    array[b] = tmp;
}

int compute_average(Finger* f, int val)
{
    // shift (call swap function)
    for (int i = 0; i < AVG_THRESHOLD - 1; i++) {
      swap(f->history, i, i + 1);
    }
    // insert new value at end of arr
    f->history[AVG_THRESHOLD-1] = val;
    // compute dot product with weights?
    float weighted_sum = dot_product(f->history, weights, AVG_THRESHOLD);
    // divide by AVG_THRESHOLD
    return (int) (weighted_sum/(float)AVG_THRESHOLD);
}

float dot_product(int* arr1, float* arr2, int length) {
  float sum = 0;
  for (int i = 0; i < length; i ++) {
    sum += (float) arr1[i] * (float) arr2[i];
  }
  return sum;
}

// automatically read sensor and write to the servo
void finger_move(Finger* f)
{
  int val = finger_read(f);
  //finger_write(f, val);
}

// Arduino setup function
void setup() {
    Serial.begin(9600);
    pinMode(CALIBRATE_BUTTON, INPUT_PULLUP);
    pinMode(CALIBRATE_LED, OUTPUT);

    for (int i=0;i<NUM_FINGERS;i++){
      finger_setup(&fingers[i], i, PWM_PINS[i], 1);
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
    for (int i=INDEX;i<=INDEX;i++){
      
      finger_move(&fingers[i]);
      delay(1);
    }
  }
}
