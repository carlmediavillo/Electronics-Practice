#include <Stepper.h>

const int stepsPerRevolution = 200;  
// change this to fit the number of steps per revolution for your motor

// initialize the stepper library on pins 2 through 5:
Stepper myStepper(stepsPerRevolution, 2, 3, 4, 5);

void setup() {
  pinMode(7, INPUT);
  // set the speed at 60 rpm:
  myStepper.setSpeed(60);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(7) == LOW) {
    // step one revolution  in one direction:
    Serial.println("clockwise");
    myStepper.step(stepsPerRevolution);
  }
}
