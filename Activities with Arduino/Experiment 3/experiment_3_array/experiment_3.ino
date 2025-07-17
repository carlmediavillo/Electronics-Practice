#include "Arduino.h"

int LEDarray[8] = {3,4,5,6,7,8,9,10};
int soundSensor = 2;
int sensorSound = analogRead(A0);
int sensorLight = analogRead(A1);
boolean LEDStatus = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(soundSensor, INPUT);
  pinMode(LEDarray[8], OUTPUT);
  pinMode(sensorSound, OUTPUT);
  pinMode(sensorLight, OUTPUT);
  
}

void loop() {
  int sensorSound=analogRead(sensorSound);
  int SensorData=digitalRead(soundSensor);   
     if(sensorSound>=800) {
         digitalWrite(LEDarray[7],HIGH);
    }
      else{
        LEDStatus=false;
        digitalWrite(LEDarray[7],LOW);
      }
     if(sensorSound>=750) {
         digitalWrite(LEDarray[6],HIGH);
     }
      else{
        LEDStatus=false;
        digitalWrite(LEDarray[6],LOW);
    }
     if(sensorSound>=700) {
         digitalWrite(LEDarray[5],HIGH);
     }
      else{
        LEDStatus=false;
        digitalWrite(LEDarray[5],LOW);
    }
      
     if(sensorSound>=650) {
         digitalWrite(LEDarray[4],HIGH);
     }
      else{
        LEDStatus=false;
        digitalWrite(LEDarray[4],LOW);
      }

 int sensorLight = analogRead(A1);
 double dV = sensorLight;
 double le = (dV/1023)*100;
 int level = le;

      if(level>=0) {
         digitalWrite(LEDarray[3],HIGH);
     }
      else{
        LEDStatus=false;
        digitalWrite(LEDarray[3],LOW);
      }
      if(level>=5) {
         digitalWrite(LEDarray[2],HIGH);
     }
      else{
        LEDStatus=false;
        digitalWrite(LEDarray[2],LOW);
      }
      if(level>=10) {
         digitalWrite(LEDarray[1],HIGH);
     }
      else{
        LEDStatus=false;
        digitalWrite(LEDarray[1],LOW);
      }
      if(level>=50) {
         digitalWrite(LEDarray[0],HIGH);
     }
      else{
        LEDStatus=false;
        digitalWrite(LEDarray[0],LOW);
      }
    }
    
