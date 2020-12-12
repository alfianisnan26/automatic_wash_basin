#include <Servo.h>

class outputs {
  private:
    bool stateKERAN=false;
    bool stateSABUN=false;
    Servo SERVO_S;
    Servo SERVO_K;
    int LED_S = 4;
    int LED_K = 7;
    int VA_S = 6;
    int VA_K = 5;
    int pos = 0;
  
  public:
  void init() {
    pinMode(LED_S, OUTPUT);
    pinMode(LED_K, OUTPUT);
    SERVO_K.attach(VA_K);  // servo keran
    SERVO_S.attach(VA_S);  // servo sabun
  }
  
  void keran(bool stateKERAN){
    if(stateKERAN==true) {
       for (pos=90;pos>=0;pos--){ //perulangan untuk variabel a dari 90 ke 0 derajat
        SERVO_K.write(pos);       //Keran membuka
        delay(10);                // waktu jeda 10 ms
      }
    }
     else {
        for (pos=0;pos<=90;pos++){ //perulangan untuk variabel a dari 0 ke 90 derajat
           SERVO_K.write(pos);     //Keran menutup  
           delay(10);              // waktu jeda 10 ms
        }
    }
  }

   void keran_led(bool stateKERAN){
     if(stateKERAN == true){
        digitalWrite(LED_K, HIGH);
        delay(1000);
        digitalWrite(LED_K, LOW);
        delay(1000);
     }
     else digitalWrite(LED_K, LOW);
    }

  void sabun(bool stateSABUN){
      for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        SERVO_S.write(pos);                 // tell servo to go to position in variable 'pos'
        delay(10);                           // waits 10ms for the servo to reach the position
      }
      for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
        SERVO_S.write(pos);                 // tell servo to go to position in variable 'pos'
        delay(10);                          // waits 10ms for the servo to reach the position
      }
    }

   void sabun_led(bool stateSABUN){
     if(stateSABUN == true){
        digitalWrite(LED_S, HIGH);
        delay(1000);
        digitalWrite(LED_S, LOW);
        delay(1000);
     }
     else digitalWrite(LED_S, LOW);
   }  
}OUTPUTS;
