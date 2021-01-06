#include<Wire.h>
#include "RTClib.h"


class CLASS_RTC{
  RTC_DS1307 RTC;
  word current_minute;
  word current_hour;
  word current_day;
  word current_month;
  word current_year;
  public:
  void init()
  {
    Wire.begin();
    RTC.begin(); // load the time from your computer.
    if (! RTC.isrunning())
    {
      Serial.println("RTC is NOT running!");// This will reflect the time that your sketch was compiled
      RTC.adjust(DateTime(__DATE__, __TIME__));
    }
  }

  bool update(byte x, byte line, word current, word value, char endLine){
    if(current!=value){
      lcd.setCursor(x,line);
      if(value<10) lcd.print('0');
      lcd.print(value);
      if(endLine!=NULL) lcd.print(endLine);
    }
    return false;
  }
  bool blinker = false;
  void showOnLCD(byte line){
    if(!blinker){
      blinker = true;
      lcd.noBlink();
      lcd.noCursor();
    }
    DateTime now = RTC.now();
    if(update(0,line, current_hour, now.hour(),':')) current_hour = now.hour();
    if(update(3,line, current_minute, now.minute(),NULL)) {
      p("update minute");
      current_minute = now.minute();
    }
    if(update(10, line, current_day, now.day(),'/')) current_day = now.day();
    if(update(13, line, current_month, now.month(),'/')) current_month = now.month();
    if(update(16, line, current_year, now.year(),NULL)) current_year = now.year();
  }
  void clearLCD(byte line){
    blinker = false;
    current_minute = 0xFF;
    current_hour = 0xFF;
    current_day = 0xFF;
    current_month = 0xFF;
    current_year = 0xFF;
    lcd.setCursor(0,line);
    lcd.print("                    ");
    
  }
  
}rtc;
