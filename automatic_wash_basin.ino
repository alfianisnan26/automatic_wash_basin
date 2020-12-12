#include "pin.h";
#include "alfian.h";
bool state = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Initialize Weight");
  WEIGHT.init();
}

void loop() {
  Serial.println(analogRead(A0));
  delay(500);
}
