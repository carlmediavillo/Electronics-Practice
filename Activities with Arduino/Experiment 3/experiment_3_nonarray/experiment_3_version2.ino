#include "Arduino.h"

int LED1 = 3;
int LED2 = 4;
int LED3 = 5;
int LED4 = 6;
int LED5 = 7;
int LED6 = 8;
int LED7 = 9;
int LED8 = 10;
int soundSensor = 2;
int sensorSound = analogRead(A0);
int sensorLight = analogRead(A1);
boolean LEDStatus = false;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(soundSensor, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(LED8, OUTPUT);
  pinMode(sensorSound, OUTPUT);
  pinMode(sensorLight, OUTPUT);
  
}

void loop() {
  int sensorSound=analogRead(sensorSound);
  int SensorData=digitalRead(soundSensor);   
     if(sensorSound>=800) {
         digitalWrite(LED8,HIGH);
    }
      else{
        LEDStatus=false;
        digitalWrite(LED8,LOW);
      }
     if(sensorSound>=750) {
         digitalWrite(LED7,HIGH);
     }
      else{
        LEDStatus=false;
        digitalWrite(LED7,LOW);
    }
     if(sensorSound>=700) {
         digitalWrite(LED6,HIGH);
     }
      else{
        LEDStatus=false;
        digitalWrite(LED6,LOW);
    }
      
     if(sensorSound>=650) {
         digitalWrite(LED5,HIGH);
     }
      else{
        LEDStatus=false;
        digitalWrite(LED5,LOW);
      }

 int sensorLight = analogRead(A1);
 double dV = sensorLight;
 double le = (dV/1023)*100;
 int level = le;

      if(level>=0) {
         digitalWrite(LED4,HIGH);
     }
      else{
        LEDStatus=false;
        digitalWrite(LED4,LOW);
      }
      if(level>=5) {
         digitalWrite(LED3,HIGH);
     }
      else{
        LEDStatus=false;
        digitalWrite(LED3,LOW);
      }
      if(level>=10) {
         digitalWrite(LED2,HIGH);
     }
      else{
        LEDStatus=false;
        digitalWrite(LED2,LOW);
      }
      if(level>=50) {
         digitalWrite(LED1,HIGH);
     }
      else{
        LEDStatus=false;
        digitalWrite(LED1,LOW);
      }
    }
    
