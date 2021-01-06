
class US_SENSOR{
  byte pin;
  public:
  bool state = false;
  bool lastState = true;
  int onTrig;
  int offTrig;
  int distance;
  US_SENSOR(byte pin, int onTrig, int offTrig){
    this->pin = pin;
    this->onTrig = onTrig;
    this->offTrig = offTrig;
  }
  bool updateState(){
    lastState = state;
    return state;
  }
  long read(){
    outPin(pin);
    offPin(pin); dms(2);
    onPin(pin); dms(10);
    offPin(pin);
    inPin(pin);
    long ret = (long)pulseIn(pin, HIGH);
    if(ret!=0) distance =  (int)(ret * 0.0349 / 2);
    return distance;
  }
  
  bool get() {
    read();
    if(distance < onTrig) state = true;
    else if(distance > offTrig)state = false;
    return state;

  }
  
};

class ULTRASONIC{
  public:
  US_SENSOR sink = US_SENSOR(US_SI, 90, 100);
  US_SENSOR kran = US_SENSOR(US_KR, 10, 15);
  US_SENSOR sabun= US_SENSOR(US_SA, 7, 8);
}us;
