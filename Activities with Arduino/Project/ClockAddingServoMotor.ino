#include <LiquidCrystal_I2C.h>
#include <DS1302.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
DS1302 rtc(2, 3, 4); //CE, IO, CLK
Servo myServo;

const int button1 = 13;
const int button2 = 12;

const int led11 = 11;
const int led12 = 10;
const int led21 = 9;
const int led22 = 8;

const int buzzer = 5;

//bool buzzerState = false;
bool alarmStatus = false;
bool servoDir = true;

bool led11State = false;
bool led12State = false;
bool led21State = false;
bool led22State = false;

bool lastButton1State = false;
bool lastButton2State = false;
bool button1State;
bool button2State;

unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
unsigned long button1Timer = 0;
unsigned long button2Timer = 0;

unsigned long debounceDelay = 100;
unsigned long longPressTime = 1000;

byte clkState = 1;
byte clkMode = 1;
byte servoPos = 90;

int reg_hh;
int reg_mm;
int reg_ss;

int reg_YY;
int reg_MM;
int reg_DD;

int reg_hh_alarm = 0;
int reg_mm_alarm = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(led11, OUTPUT);
  pinMode(led12, OUTPUT);
  pinMode(led21, OUTPUT);
  pinMode(led22, OUTPUT);
  pinMode(buzzer, OUTPUT);

  myServo.attach(6);

  digitalWrite(led11, led11State);
  digitalWrite(led12, led12State);
  digitalWrite(led21, led21State);
  digitalWrite(led22, led22State);
  digitalWrite(buzzer, LOW);
  
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  
  rtc.halt(false);
  rtc.writeProtect(false);

  Serial.begin(9600);
  
  //rtc.setDOW(FRIDAY);
  //rtc.setTime(0, 0, 0);
  //rtc.setDate(1, 1, 2021);
}

void loop() {
  // put your main code here, to run repeatedly:
  int reading1 = digitalRead(button1);
  int reading2 = digitalRead(button2);
  Time t = rtc.getTime();
  
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
          //Button 1 Long Press
          led12State = !led12State;
          switch(clkMode) {
            case 0:
              switch(clkState) {
                case 0:
                  clkMode = 1;
                  clkState = 1;
                  alarmStatus = false;
                break;
              }
            break;
          }
        }
        else {
          //Button 1 Short Press
          led11State = !led11State;
          switch(clkMode) {
            case 0:
              switch(clkState) {
                case 0:
                  clkMode = 1;
                  clkState = 1;
                  alarmStatus = false;
                break;
              }
            break;

            case 1:
              switch(clkState) {
                case 1:
                  clkMode = 2;
                  //Change Mode to Alarm
                  Serial.println(clkMode);
                break;

                case 2:
                  reg_hh++;
                  if (reg_hh == 24) {
                    reg_hh = 0;
                  }
                break;

                case 3:
                  reg_mm++;
                  if (reg_mm == 60) {
                    reg_mm = 0;
                  }
                break;

                case 4:
                  reg_ss = 0;
                break;

                case 5:
                  reg_YY++;
                  if (reg_YY == 2100) {
                    reg_YY = 2000;
                  }
                break;

                case 6:
                  reg_MM++;
                  if (reg_MM == 13) {
                    reg_MM = 1;
                  }
                break;

                case 7:
                  reg_DD++;
                  switch(reg_MM) {
                    case 1:
                      if (reg_DD == 32) {
                        reg_DD = 1;
                      }
                    break;

                    case 2:
                      if (reg_YY % 4 == 0) {
                        if (reg_DD == 30) {
                          reg_DD = 1;
                        }
                      }
                      else {
                        if (reg_DD == 29){
                          reg_DD = 1;
                        }
                      }
                    break;

                    case 3:
                      if (reg_DD == 32) {
                        reg_DD = 1;
                      }
                    break;

                    case 4:
                      if (reg_DD == 31) {
                        reg_DD = 1;
                      }
                    break;

                    case 5:
                      if (reg_DD == 32) {
                        reg_DD = 1;
                      }
                    break;

                    case 6:
                      if (reg_DD == 31) {
                        reg_DD = 1;
                      }
                    break;

                    case 7:
                      if (reg_DD == 32) {
                        reg_DD = 1;
                      }
                    break;

                    case 8:
                      if (reg_DD == 32) {
                        reg_DD = 1;
                      }
                    break;

                    case 9:
                      if (reg_DD == 31) {
                        reg_DD = 1;
                      }
                    break;

                    case 10:
                      if (reg_DD == 32) {
                        reg_DD = 1;
                      }
                    break;

                    case 11:
                      if (reg_DD == 31) {
                        reg_DD = 1;
                      }
                    break;

                    case 12:
                      if (reg_DD == 32) {
                        reg_DD = 1;
                      }
                    break;
                  }
                break;
              }
            break;
            
            case 2:
              switch(clkState) {
                case 1:
                  clkMode = 3;
                  //Change Mode to Servo
                  Serial.println(clkMode);
                break;

                case 2:
                  reg_hh_alarm++;
                  if (reg_hh_alarm == 24) {
                    reg_hh_alarm = 0;
                  }
                break;

                case 3:
                  reg_mm_alarm++;
                  if (reg_mm_alarm == 60) {
                    reg_mm_alarm = 0;
                  }
                break;

                case 4:
                  alarmStatus = !alarmStatus;
                break;
              }
            break;

            case 3:
              switch(clkState) {
                case 1:
                  clkMode = 1;
                  //Change Mode to Clock Display
                  Serial.println(clkMode);
                break;

                case 2:
                  servoDir = !servoDir;
                break;

                case 3:
                  if (servoDir == true) {
                    if (servoPos < 180) {
                      servoPos += 90;
                    }
                  }
                  else {
                    if (servoPos > 0) {
                      servoPos -= 90;
                    }
                  }
                break;
              }
            break;
          }
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
          //Button 2 Long Press
          led22State = !led22State;
          switch(clkMode) {
            case 0:
              switch(clkState) {
                case 0:
                  clkMode = 1;
                  clkState = 1;
                  alarmStatus = false;
                break;
              }
            break;

            case 1:
              reg_hh = t.hour;
              reg_mm = t.min;
              reg_ss = t.sec;

              reg_YY = t.year;
              reg_MM = t.mon;
              reg_DD = t.date;
              
              switch(clkState) {
                case 1:
                  clkState = 2;
                  //go to State for setting hours
                  Serial.println(clkState);
                break;
              }
            break;

            case 2:
              switch(clkState) {
                case 1:
                  clkState = 2;
                  //Go to State for Setting Alarm Hours
                  Serial.println(clkState);
                break;
              }
            break;

            case 3:
              switch(clkState) {
                case 1:
                  clkState = 2;
                  //go to State for setting servo direction
                  Serial.println(clkState);
                break;
              }
            break;
          }
        }
        else {
          //Button 2 Short Press
          led21State = !led21State;
          switch(clkMode) {
            case 0:
              switch(clkState) {
                case 0:
                  clkMode = 1;
                  clkState = 1;
                  alarmStatus = false;
                break;
              }
            break;
            
            case 1:
              switch(clkState) {
                case 2:
                  clkState = 3;
                  //go to State for setting minutes
                  Serial.println(clkState);
                break;

                case 3:
                  clkState = 4;
                  //go to State for resetting seconds
                  Serial.println(clkState);
                break;

                case 4:
                  rtc.setTime(reg_hh, reg_mm, reg_ss);
                  clkState = 5;
                  //go to State for setting year
                  Serial.println(clkState);
                break;

                case 5:
                  clkState = 6;
                  //go to State for setting month
                  Serial.println(clkState);
                break;

                case 6:
                  clkState = 7;
                  //go to State for setting day;
                  Serial.println(clkState);
                break;

                case 7:
                  rtc.setDate(reg_DD, reg_MM, reg_YY);
                  clkState = 1;
                  //exit setup
                  Serial.println(clkState);
                break;
              }
            break;

            case 2:
              switch(clkState) {
                case 2:
                  clkState = 3;
                  //go to state for Setting Alarm Minutes
                  Serial.println(clkState);
                break;

                case 3:
                  clkState = 4;
                  //go to state for changing alarm status
                  Serial.println(clkState);
                break;

                case 4:
                  clkState = 1;
                  //Exit Alarm Setting
                  Serial.println(clkState);
                break;
              }
            break;

            case 3:
              switch(clkState) {
                case 2:
                  clkState = 3;
                  //go to state for changing servo position
                  Serial.println(clkState);
                break;

                case 3:
                  clkState = 1;
                  //Exit servo setting
                  Serial.println(clkState);
                break;
              }
            break;
          }
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

  myServo.write(servoPos);

  //buzzer sound
  if (alarmStatus == false) {
    digitalWrite(buzzer, LOW);
  }
  else {
    if (reg_hh_alarm == t.hour && reg_mm_alarm == t.min) {
      digitalWrite(buzzer, HIGH);
      clkMode = 0;
      clkState = 0;
    }
  }
    
  
  //LCD Displays
  if (clkMode == 0) {
    switch(clkState) {
      case 0:
        lcd.setCursor(0, 0);
        lcd.print("DATE: ");
        lcd.print(rtc.getDateStr(FORMAT_LONG, FORMAT_MIDDLEENDIAN));
        
        lcd.setCursor(0, 1);
        lcd.print("TIME: ");
        lcd.print(rtc.getTimeStr(FORMAT_LONG));
        lcd.print("     ");
      break;
    }
  }
  
  if (clkMode == 1) {
    switch(clkState) {
      case 1:
        lcd.setCursor(0, 0);
        lcd.print("DATE: ");
        lcd.print(rtc.getDateStr(FORMAT_LONG, FORMAT_MIDDLEENDIAN));
        
        lcd.setCursor(0, 1);
        lcd.print("TIME: ");
        lcd.print(rtc.getTimeStr(FORMAT_LONG));
        lcd.print("     ");
      break;

      case 2 ... 4:
        lcd.setCursor(0, 0);
        lcd.print("SETUP ENABLED!  ");
    
        lcd.setCursor(0, 1);
        lcd.print("TIME: ");
        if (reg_hh < 10) {
          lcd.print("0");
        }
        lcd.print(reg_hh);
        lcd.print(":");

        if (reg_mm < 10) {
          lcd.print("0");
        }
        lcd.print(reg_mm);
        lcd.print(":");

        if (reg_ss < 10) {
          lcd.print("0");
        }
        lcd.print(reg_ss);
        lcd.print("  ");
      break;

      case 5 ... 7:
        lcd.setCursor(0, 0);
        lcd.print("SETUP ENABLED!  ");

        lcd.setCursor(0, 1);
        lcd.print("DATE: ");
        if (reg_MM < 10) {
          lcd.print("0");
        }
        lcd.print(reg_MM);
        lcd.print(".");

        if(reg_DD < 10) {
          lcd.print("0");
        }
        lcd.print(reg_DD);
        lcd.print(".");
        lcd.print(reg_YY);
      break;
    }
  }

  if (clkMode == 2) {
    switch(clkState) {
      case 1:
        lcd.setCursor(0, 0);
        lcd.print("Alarm: ");
        if (reg_hh_alarm < 10) {
          lcd.print("0");
          lcd.print(reg_hh_alarm);
        }
        else {
          lcd.print(reg_hh_alarm);
        }
        lcd.print(":");
        
        if (reg_mm_alarm < 10) {
          lcd.print("0");
          lcd.print(reg_mm_alarm);
        }
        else {
          lcd.print(reg_mm_alarm);
        }
        lcd.print("    ");

        lcd.setCursor(0, 1);
        lcd.print("Active: ");
        if (alarmStatus == true) {
          lcd.print("Yes     ");
        }
        else {
          lcd.print("No      ");
        }
        break;
        
      case 2 ... 3:
        lcd.setCursor(0, 0);
        lcd.print("SETUP ENABLED!  ");

        lcd.setCursor(0, 1);
        lcd.print("Alarm: ");
        if (reg_hh_alarm < 10) {
          lcd.print("0");
          lcd.print(reg_hh_alarm);
        }
        else {
          lcd.print(reg_hh_alarm);
        }
        lcd.print(":");
        
        if (reg_mm_alarm < 10) {
          lcd.print("0");
          lcd.print(reg_mm_alarm);
        }
        else {
          lcd.print(reg_mm_alarm);
        }
        lcd.print("    ");
      break;

      case 4:
        lcd.setCursor(0, 0);
        lcd.print("Alarm Status:");

        lcd.setCursor(0, 1);
        lcd.print("             ");
        if (alarmStatus == true) {
          lcd.print("ON ");
        }
        else {
          lcd.print("OFF");
        }
      break;
    }
  }

  if (clkMode == 3) {
    switch(clkState) {
      case 1:
        lcd.setCursor(0, 0);
        lcd.print("Servo Position: ");

        lcd.setCursor(0, 1);
        lcd.print("             ");
        switch(servoPos) {
          case 0 ... 9:
            lcd.print("  ");
          break;

          case 10 ... 99:
            lcd.print(" ");
          break;

          case 100 ... 180:
          break;
        }
        lcd.print(servoPos);
      break;

      case 2:
        lcd.setCursor(0, 0);
        lcd.print("Alter direction?");

        lcd.setCursor(0, 1);
        if(servoDir == true) {
          lcd.print("Active: Positive");
        }
        else {
          lcd.print("Active: Negative");
        }
      break;

      case 3:
        lcd.setCursor(0, 0);
        lcd.print("Change Position?");

        lcd.setCursor(0, 1);
        lcd.print("Active: ");
        lcd.print(servoPos);
        switch(servoPos) {
          case 0 ... 9:
            lcd.print("       ");
          break;

          case 10 ... 99:
            lcd.print("      ");
          break;

          case 100 ... 180:
            lcd.print("     ");
          break;
       }
    }
  }
}
