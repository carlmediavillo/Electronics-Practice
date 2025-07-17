#include <Servo.h>

Servo myservo;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  myservo.attach(3);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(2) == LOW) {
    for (int pos = 0; pos <= 180; pos += 2) {
      myservo.write(pos);
      Serial.println(pos);
      delay(1);
    }
    for (int pos = 180; pos >= 0; pos -= 2) {
      myservo.write(pos);
      Serial.println(pos);
      delay(1);
    }
  }
}
