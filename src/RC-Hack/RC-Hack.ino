const int forward = 2;
const int backwards = 3;
const int right = 3;
const int left = 4;

void setup() {
  pinMode(forward, OUTPUT);
  pinMode(backwards, OUTPUT);
  pinMode(right, OUTPUT);
  pinMode(left, OUTPUT);
}

void loop() {
  digitalWrite(forward, HIGH);
  delay(500);
  digitalWrite(forward, LOW);
  delay(1000);
  digitalWrite(backwards, HIGH);
  delay(500);
  digitalWrite(backwards, LOW);
  delay(1000);
}
