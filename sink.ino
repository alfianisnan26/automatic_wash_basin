#include "kevin.h";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  OUTPUTS.init();
}

void loop() {
  // put your main code here, to run repeatedly:
  OUTPUTS.sabun(true);
  OUTPUTS.sabun_led(true);
}
