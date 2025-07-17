#include "Wire.h"
#include "LiquidCrystal_PCF8574.h"
#include "LiquidCrystal_I2C.h"
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3,POSITIVE);

LiquidCrystal_PCF8574 LCDi2C;

int soundSensor=2; 
int level = analogRead(A0); 

void setup () {
  lcd.begin(16,2);
  lcd.clear();
  lcd.print("Starting");
  delay(500);
  Serial.begin(9600);
  pinMode(soundSensor,INPUT); 
  pinMode(level, OUTPUT);
}

void loop() {
  int soundSensor=2; 
  int level = analogRead(A0); 
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Sound LEVEL:");
 lcd.print(level);
 lcd.setCursor(0, 1);
 
 if ((level >= 0) && (level <= 600))
 {
  lcd.print("Weak"); 
 }
 else if ((level > 600) && (level <= 700))
 {
  lcd.print("Medium"); 
 }
 else
 {
  lcd.print("Strong"); 
 }
 delay(500); 
}
    

   
   
