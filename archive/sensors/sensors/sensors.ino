#define BUF_SIZE 6

#define VCC 5

// bend sensors
#define BEND_STRAIGHT 880
#define BEND_FLEX 580
#define R_DIV 56000

// fingers
#define INDEX_PIN 0
#define MIDDLE_PIN 1
#define RING_PIN 2
#define PINKIE_PIN 3
#define THUMB_PIN 4
#define WRIST_PIN 5
#define POT_PIN 6

// potentiomenter
// todo fill values
#define POT_NONE 0
#define POT_FULL 0
#define POT_MAP 0

int buffer[BUF_SIZE];

void setup() {
    Serial.begin(9600);
    pinMode(INDEX_PIN, INPUT);
    pinMode(MIDDLE_PIN, INPUT);
    pinMode(RING_PIN, INPUT);
    pinMode(PINKIE_PIN, INPUT);
    pinMode(THUMB_PIN, INPUT);
    pinMode(WRIST_PIN, INPUT);
    pinMode(POT_PIN, INPUT);
}

int readFlexSensor(int pin)
{
    int value = analogRead(pin);
    float flexV = value * VCC / 1023.0;
    float flexR = R_DIV * (VCC / flexV - 1.0);
    return map(flexR, BEND_STRAIGHT, BEND_FLEX, 0, 90);
}

void loop() {
    /*for (int i=INDEX_PIN; i<WRIST_PIN+1; i++)
    {
        buffer[i] = readFlexSensor(i);
    }
    Serial.write(buffer, BUF_SIZE);*/
    Serial.print(readFlexSensor(INDEX_PIN));
    Serial.print(" - ");
    Serial.println(analogRead(INDEX_PIN));
    delay(10);
}
