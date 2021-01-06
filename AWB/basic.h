#include "pin.h"
#define onPin(x) digitalWrite(x, HIGH)
#define offPin(x) digitalWrite(x, LOW)
#define outPin(x) pinMode(x, OUTPUT)
#define inPin(x) pinMode(x, INPUT)
#define p Serial.print
#define pl Serial.println
#define r digitalRead
#define ra analogRead
#define d delay
#define dms delayMicroseconds


class DNB{
  private:
  bool autoReload = false;
  bool last_state = true;
  public:
  bool state = true;
  int initial = 0;
  int count = 0;
  void clear(){
    count = 0;
    state = true;
    last_state = true;
  }
  bool run(){
    if(this->count == 0){
      if(autoReload) this->count = this->initial;
      state = true;
      return true;
    }
    delay(1);
    this->count--;
    state = false;
    return false;
  }
  int load(const int value, bool autoreload){
    this->autoReload = autoreload;
    this->initial = value;
    this->count = value;
    return value;
  }
  bool hasData(){
    if(state != last_state){
      last_state = state;
      return true;
    }
    else return false;
  }
};

#include "keypad.h"
#include "lcd.h"
#include "ultrasonic.h"
#include "rtc.h"
#include "thermometer.h"
