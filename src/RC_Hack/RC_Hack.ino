//Libaries
#include <NewPing.h>

//Set up NewPing

#define TRIGGER_PIN  9  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     8  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

//RC Controls

int forward = 11;
int backwards = 10;
int left = 13;
int right = 12;

int run_speed = 125;

int turn_wait = 1250;
int turn_between_next = 300;

//Sensor
int converted_sensor_distance = 0;
int pingTimer = 15;
int min_sensor_distance = 10;

void setup() {
  //RC controls
  pinMode(forward, OUTPUT);
  pinMode(backwards, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);
}

void loop() {
  if (millis() >= pingTimer) {   //pingSpeed milliseconds since last ping, do another ping.
    unsigned long sensor_distance = sonar.ping();    //Updates distance of ultraonic sensor
    converted_sensor_distance = sensor_distance / US_ROUNDTRIP_CM;    //Converts to CM
  }
  
  if (converted_sensor_distance < min_sensor_distance && converted_sensor_distance > 0){
    digitalWrite(forward, LOW);
    delay(300);
    
    //Turn
    digitalWrite(left, HIGH);
    digitalWrite(backwards, HIGH);
    delay(turn_wait);
    digitalWrite(left, LOW);
    digitalWrite(backwards, LOW);
    delay(turn_between_next);
  } else {
    analogWrite(forward, run_speed);
  }
}
