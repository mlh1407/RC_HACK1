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

int run_speed = 100;

//Sensor
int converted_sensor_distance = 0;
int pingTimer = 15;
int min_sensor_distance = 10;

int smother_sum = 0;
int debounced_sensor_distance = 0;

void setup() {
  //RC controls
  pinMode(forward, OUTPUT);
  pinMode(backwards, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);
}

void loop() {
  for (int counter = 0;counter < 5;counter++) {
    unsigned long sensor_distance = sonar.ping();    //Updates distance of ultraonic sensor
    smother_sum += sensor_distance;
    
    delay(pingTimer);
  }
  
  debounced_sensor_distance = smother_sum / 5;
  
  converted_sensor_distance = debounced_sensor_distance / US_ROUNDTRIP_CM;    //Converts to CM
  smother_sum = 0;
  
  if (converted_sensor_distance < min_sensor_distance){
    digitalWrite(forward, LOW);
    
    //Turn
    digitalWrite(left, HIGH);
    digitalWrite(backwards, HIGH);
    delay(300);
    digitalWrite(left, LOW);
    digitalWrite(backwards, LOW);
    delay(100);
    
    digitalWrite(right, HIGH);
    digitalWrite(forward, HIGH);
    delay(300);
    digitalWrite(right, LOW);
    digitalWrite(forward, LOW);
    delay(100);
  } else {
    analogWrite(forward, run_speed);
  }
}
