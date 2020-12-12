#include "HX711.h"

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
    return this->loadcell.get_units(10);
  }
  
} WEIGHT;
