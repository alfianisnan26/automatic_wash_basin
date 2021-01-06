#include "HX711.h"
#include "pin.h"
#include <Wire.h> // Include Wire.h to control I2C
#include <LiquidCrystal_I2C.h> //Download & include the code library can be downloaded below

class class_sensorWeight{
  private:
  HX711 loadcell;
  const int SDA = pinSDA;
  const int SCL = pinSCL;
  long LOADCELL_OFFSET = 50682624;
  long LOADCELL_DIVIDER = 5895655;
  long lastRead = 0;
  long minimumValue;
  public:
  void setLoadCell(long loadOffset, long loadDivider){
    this->LOADCELL_OFFSET = loadOffset;
    this->LOADCELL_DIVIDER = loadDivider;    
  }

  void setMinimumValue(long val){
    this->minimumValue = val;
  }
  
  bool minimumValueTriggered(){
    long readVal = this->loadcell.get_units(10);
    if(readVal<this->minimumValue){
      return true;
    }
    return false;
  }

  void init(){
    this->loadcell.begin(this->SDA, this->SCL);
    this->loadcell.set_scale(this->LOADCELL_DIVIDER);
    this->loadcell.set_offset(this->LOADCELL_OFFSET);
  }

  long getValue(){
    return this->loadcell.get_units();
  }
  
} WEIGHT;

class key_string(){
   private:
   LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);
   const int KEYA = pinKEYA;
   const int KEYB = pinKEYB;
   const int KEYC = pinKEYC;
   const int KEYD = pinKEYD;
   cosnt int KEYS = pinKEYS;
   byte getData(){
    byte ret = 0;
    if(digitalRead(KEYA)) ret + 1;
    if(digitalRead(KEYB)) ret + 2;
    if(digitalRead(KEYC)) ret + 4;
    if(digitalRead(KEYD)) ret + 8;
    return ret;
   }
   public:
   void init(bool slcd){
    pinMode(KEYA, INPUT);
    pinMode(KEYB, INPUT);
    pinMode(KEYC, INPUT);
    pinMode(KEYD, INPUT);
    if(slcd){
      lcd.begin (16,2);
    }
   }

   String getString(bool isNumberOnly){
    String foo;
    return foo;
   }
}KEY_STRING;
