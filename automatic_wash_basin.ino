#include "pin.h";
#include "alfian.h";
bool state = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Initialize Weight");
  WEIGHT.init();
}

void loop() {
  Serial.println(WEIGHT.getValue());
  delay(1000);
}
