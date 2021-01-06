#include <DS1631.h>
#include <OneWire.h>
#include <DallasTemperature.h>
OneWire oneWire(ENVT);
DallasTemperature sensors(&oneWire);
DS1631_Class DS1631;
class THERMO{
  const float maxBody = 37;
  public:
  void init(){
    DS1631.begin(I2C_STANDARD_MODE);
    sensors.begin();
    Serial.print(F("Found "));
    p(DS1631.thermometers);
    Serial.println(F(" DS1631 device(s)"));
    DS1631.setPrecision(0, 12);
    DS1631.setContinuous(0);
  }
  void envi(){
    sensors.requestTemperatures(); 
    p("TEMP: ");
    Serial.println(sensors.getTempCByIndex(2)); 
  }
  float out;
  bool lastRead;
  bool body(){
    Serial.print(F(" TEMP BODY : "));
    out = DS1631.readTemp(0) * 0.0625;
    pl(String(out) + "C");
    
    if (out > maxBody)
    {
      pl(F(" alarm raised. Thermometer "));
      lastRead = true;
      return true;
    }
    lastRead = false;
    return false;
  }
}thermo;
