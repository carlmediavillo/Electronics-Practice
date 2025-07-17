#include <LiquidCrystal_I2C.h>
#include <DS1302.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
DS1302 rtc(2, 3, 4); //CE, IO, CLK

void setup() {
  // put your setup code here, to run once:
  rtc.halt(false);
  rtc.writeProtect(false);

  lcd.begin();
  lcd.backlight();
  lcd.clear();

  //rtc.setDOW(FRIDAY);
  //rtc.setTime(0, 0, 0);
  //rtc.setDate(1, 1, 2021);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 0);
  lcd.print("DATE: ");
  lcd.print(rtc.getDateStr(FORMAT_LONG));
  
  lcd.setCursor(0, 1);
  lcd.print("TIME: ");
  lcd.print(rtc.getTimeStr(FORMAT_LONG));
}
