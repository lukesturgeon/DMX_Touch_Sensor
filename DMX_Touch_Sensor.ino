#include <CapacitiveSensor.h>

#define NUM_SENSORS 2

CapacitiveSensor sensors[NUM_SENSORS] = {
  CapacitiveSensor(4, 5),
  CapacitiveSensor(2, 3)
};

int   sensorValues[NUM_SENSORS];
int   sensorThreshold = 1500;
int   ledPin = 7;
bool  onState = false;
bool  prev_onState = false;


void setup() {
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
}

void loop() {
  // loop through each available sensor
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    // get the current sensor values
    sensorValues[i] = sensors[i].capacitiveSensor(64);

    // output to serial
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }

  // check if both are being touched
  if (sensorValues[0] > sensorThreshold && sensorValues[1] > sensorThreshold && onState == false) {
    // both are being touched
    onState = true;
  }
  else if (sensorValues[0] < sensorThreshold || sensorValues[1] < sensorThreshold) {
    // both are
    onState = false;
  }

  // state change
  if (onState == true && prev_onState == false) {
    Serial.println("on");
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(15*1000);
  }
  else if (onState == false && prev_onState == true) {
    Serial.println("off");
    digitalWrite(ledPin, LOW);
  }

  // save current state
  prev_onState = onState;

  // finish serial with a newline
  Serial.println("");

  // give a little delay to slow things down
  delay( 200 );
}
