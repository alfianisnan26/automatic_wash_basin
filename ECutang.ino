#include "pin.h";
#include "alfian.h";

void setup() {
  Serial.begin(9600);
  WEIGHT.init();
}

void loop() {
  Serial.print(WEIGHT.getValue());
}
