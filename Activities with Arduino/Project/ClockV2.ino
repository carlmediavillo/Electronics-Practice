#include <LiquidCrystal_I2C.h>
#include <DS1302.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
DS1302 rtc(2, 3, 4); //CE, IO, CLK

const int buttonPin = 13;
const int ledPin = 12;

byte clkState = 1;

int ledState = HIGH;
int lastButtonState = LOW;
int buttonState;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50; 

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, ledState);
  
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  
  rtc.halt(false);
  rtc.writeProtect(false);

  //rtc.setDOW(FRIDAY);
  //rtc.setTime(0, 0, 0);
  //rtc.setDate(1, 1, 2021);
}

void loop() {
  // put your main code here, to run repeatedly:
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        ledState = !ledState;
        switch (clkState) {
          case 1:
            clkState = 2;
            break;
          case 2:
            clkState = 1; 
            break;  
        }
      }
    }
  }
  
  digitalWrite(ledPin, ledState);
  lastButtonState = reading;
  
  if (clkState == 1) {
    lcd.setCursor(0, 0);
    lcd.print("DATE: ");
    lcd.print(rtc.getDateStr(FORMAT_LONG));
  
    lcd.setCursor(0, 1);
    lcd.print("TIME: ");
    lcd.print(rtc.getTimeStr(FORMAT_LONG));
  }

  if (clkState == 2) {
    lcd.setCursor(0, 0);
    lcd.print("SETUP ENABLED!  ");

    lcd.setCursor(0, 1);
    lcd.print("                ");
  }
}
