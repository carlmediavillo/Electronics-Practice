#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3,POSITIVE);

void setup() {
  lcd.begin(16,2);
  lcd.clear();
  lcd.print("Starting");
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(A0);
 double dV = sensorValue;
 double le = (dV/1023)*100;
 int level = le;
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("LIGHT LEVEL:");
 lcd.print(level);
 lcd.print("%");
 lcd.setCursor(0, 1);
 
 if ((level >= 0) && (level <= 5))
 {
  lcd.print("VERY DARK"); 
 }
 else if ((level > 5) && (level <= 10))
 {
  lcd.print("DARK"); 
 }
 else if ((level > 10) && (level <= 50))
 {
  lcd.print("BRIGHT"); 
 }
 else 
 {
  lcd.print("VERY BRIGHT"); 
 }
 
 delay(500); 
}
