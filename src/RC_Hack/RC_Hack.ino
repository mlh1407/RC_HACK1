//Libaries
#include <NewPing.h>

//Set up NewPing

#define TRIGGER_PIN  9  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     8  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

//RC Controls

int forward = 13;
int backwards = 12;
int left = 11;
int right = 10;

//Sensor
int converted_sensor_distance = null;

void setup() {
  //RC controls
  pinMode(forward, OUTPUT);
  pinMode(backwards, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);
  
  timer_since_start = millis();    //Starts timer since program startup.
}

void loop() {
  unsigned long sensor_distance = sonar.ping();    //Updates distance of ultraonic sensor
  converted_sensor_distance = sensor_distance / US_ROUNDTRIP_CM;    //Converts to CM
}
