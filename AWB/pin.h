#define LED_CE 53
#define LED_SA 52
#define LED_KR 51
#define KEY_S 26
#define KEY_A 25
#define KEY_B 24
#define KEY_C 23
#define KEY_D 22
#define SDA 20
#define SCL 21
#define RX 0
#define TX 1
#define US_SA 2
#define US_KR 3
#define US_SI 4
#define BUZZ 5
#define ENVT 8
#define SR_KR 10
#define SR_SA 11

class pinout{
  int myPin;
  public:
  bool state = false;
  pinout(int pin){
    this->myPin = pin;
    pinMode(myPin, OUTPUT);
  }
  void on(){
    state = true;
    digitalWrite(myPin, HIGH);
  }

  void off(){
    state = false;
    digitalWrite(myPin, LOW);
  }

  void toggle(){
    state = !state;
    digitalWrite(myPin, state);
  }
};

#include <Servo.h>
class pinservo{
  Servo servo;
  byte myPin;
  public:
  bool state = false;
  void init(byte pin){
    this->myPin = pin;
    servo.attach(myPin);
  }
  void open(){
    state = true;
    servo.write(90);
  }
  void close(){
    state = false;
    servo.write(0);
  }
  void toggle(){
    state = !state;
    servo.write((state)?90:0);
  }
};

class LED{
  public:
  pinout kran = pinout(LED_KR);
  pinout sabun = pinout(LED_SA);
  pinout cermin = pinout(LED_CE);
};

class SERVO{
  public:
  pinservo sabun;
  pinservo kran;
  void init(){
    sabun.init(SR_SA);
    sabun.close();
    kran.init(SR_KR);
    kran.close();
  }
};

class OUTINT{
  public:
  LED led;
  SERVO servo;
  void buzz(){
    tone(BUZZ, 1000);
  }
  void noBuzz(){
    noTone(BUZZ);
  }
}interface;
