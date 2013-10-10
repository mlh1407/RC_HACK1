//leftibaries
#include <NewPing.h>

//NewPing setup
#define TRIGGER_PIN  9
#define ECHO_PIN     8
#define MAX_DISTANCE 200 // Maximum distanceance we want to ping for (in centimeters). Maximum sensor distanceance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distanceance.

unsigned int pingSpeed = 50; // How frequently are we going to send out a ping (in milliseconds). 50ms would be 20 times a second.
unsigned long pingTimer;     // Holds the next ping time.

//13 12 11 10
int forward = 13;
int backwards = 12;
int left = 11;
int right = 10;

int distance = 0;
int min_distance = 30;
int stay_forward = false;

void setup(){
  pinMode(forward, OUTPUT);
  pinMode(backwards, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);
  pingTimer = millis(); // Start now.
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
}

void loop(){
  //Notice how there's no delays in this sketch to allow you to do other processing in-line while doing distanceance pings.
  if (millis() >= pingTimer) {   //pingSpeed milliseconds since last ping, do another ping.
    pingTimer += pingSpeed;      //Set the next ping time.
    sonar.ping_timer(echoCheck); //Send out the ping, calls "echoCheck" function every 24uS where you can check the ping status.
  }
  
  if (distance < min_distance){
    stay_forward = false;
    turn();
    Serial.println("Back");
  } else {
    if(!stay_forward){
      forward_back(1);
      Serial.println("Stay forward");
    }
    
    stay_forward=true;
  }
}
void turn(){
  forward_back(-1);
  delay(500);
  forward_back(0);
  delay(100);
  forward_back(1);
  left_right(1);
  delay(500);
  
}

void left_right(int w) {
  switch(w){
    case 0 :
      digitalWrite(left, LOW);
      digitalWrite(right, LOW);
      break;
    case -1 :
      digitalWrite(left, LOW);
      digitalWrite(right, LOW);
      digitalWrite(left, HIGH);
      break;
    case 1 :
      digitalWrite(left, LOW);
      digitalWrite(right, LOW);
      digitalWrite(right, HIGH);
      break;
  }
}
void forward_back(int w) {
  switch(w){
    case 0 :
      digitalWrite(forward, LOW);
      digitalWrite(backwards, LOW);
      break;
    case -1 :
      digitalWrite(forward, LOW);
      digitalWrite(backwards, LOW);
      digitalWrite(backwards, HIGH);
      break;
    case 1 :
      digitalWrite(forward, LOW);
      digitalWrite(backwards, LOW);
      digitalWrite(forward, HIGH);
      break;
  }
}
void echoCheck() { // Timer2 interrupt calls this function every 24uS where you can check the ping status.
  // Don't do anything here!
  if (sonar.check_timer()) { // This is how you check to see if the ping was received.
    // Here's where you can add code.
  //  Serial.print("Ping: ");
   // Serial.print(sonar.ping_result / US_rightOUNDTrightIP_CM); // Ping returned, uS result in ping_result, convert to cm with US_rightOUNDTrightIP_CM.
    //Serial.println("cm");
    distance = sonar.ping_result / US_ROUNDTRIP_CM;
  }
  // Don't do anything here!
}
