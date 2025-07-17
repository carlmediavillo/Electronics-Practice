#include <LiquidCrystal_I2C.h>
#include <DS1302.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
DS1302 rtc(2, 3, 4); //CE, IO, CLK

const int button1 = 13;
const int button2 = 12;

const int led11 = 11;
const int led12 = 10;
const int led21 = 9;
const int led22 = 8;

boolean led11State = false;
boolean led12State = false;
boolean led21State = false;
boolean led22State = false;

boolean lastButton1State = false;
boolean lastButton2State = false;
boolean button1State;
boolean button2State;

unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
unsigned long button1Timer = 0;
unsigned long button2Timer = 0;

unsigned long debounceDelay = 100;
unsigned long longPressTime = 1000;

byte clkState = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(led11, OUTPUT);
  pinMode(led12, OUTPUT);
  pinMode(led21, OUTPUT);
  pinMode(led22, OUTPUT);

  digitalWrite(led11, led11State);
  digitalWrite(led12, led12State);
  digitalWrite(led21, led21State);
  digitalWrite(led22, led22State);
  
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
  int reading1 = digitalRead(button1);
  int reading2 = digitalRead(button2);
  
  //Button1 Debounce
  //Check if the button changes state
  if (reading1 != lastButton1State) {
    lastDebounceTime1 = millis();
    //Sets the basis of the debouncing  
  }

  //Check if the debouncing passes
  if ((millis() - lastDebounceTime1) > debounceDelay) {

    //Parity checking
    if (reading1 != button1State) {
      //Syncs button state to actual state
      button1State = reading1;

      if (button1State == HIGH) {
        button1Timer = millis();
      }
      
      if (button1State == LOW) {
        if ((millis() - button1Timer) > longPressTime) {
          led12State = !led12State;
          switch (clkState) {
            case 1:
              clkState = 2;
              break;
            case 2:
              clkState = 1; 
              break;  
          }
        }
        else {
          led11State = !led11State;  
        }
      }
    } 
  }

  //Button2 Debounce
  //Check if the button changes state
  if (reading2 != lastButton2State) {
    lastDebounceTime2 = millis();
    //Sets the basis of the debouncing  
  }

  //Check if the debouncing passes
  if ((millis() - lastDebounceTime2) > debounceDelay) {

    //Parity checking
    if (reading2 != button2State) {
      //Syncs button state to actual state
      button2State = reading2;

      if (button2State == HIGH) {
        button2Timer = millis();
      }
      
      if (button2State == LOW) {
        if ((millis() - button2Timer) > longPressTime) {
          led22State = !led22State;  
        }
        else {
          led21State = !led21State;  
        }
      }
    } 
  }

  lastButton1State = reading1;
  lastButton2State = reading2;
  
  digitalWrite(led11, led11State);
  digitalWrite(led12, led12State);
  digitalWrite(led21, led21State);
  digitalWrite(led22, led22State);
  
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
