class KEYPAD{
  byte* myPin;
  byte myDA;
  bool state = false;
  public:
  byte input = NULL;
  bool isBuff = false;
  void init(const byte* pin){
    this->myPin = pin;
    this->myDA = pin[0];
    for(int a=0;a<5;a++){
      inPin(pin[a]);
      p("Set Output PIN");
      pl(pin[a]);
    }
  }
  byte value(){
    this->input = 0;
    for(int a=1;a<5;a++){
      if(r(this->myPin[a])){
        switch(a){
          case 1: input+=1; break;
          case 2: input+=2; break;
          case 3: input+=4; break;
          case 4: input+=8; break;
        }
      }
      else{
      }
    }
    this->isBuff = true;
    return input;
  }
  bool check(){
    if(r(this->myDA) && !this->state){
      this->value();
      state = true;
      return true;
    }else if(!r(this->myDA) && this->state){
      state = false;
      return false;
    }
  }
   char toChar(){
    this->isBuff = false;
    switch(this->input){
      case 0: return '1';
      case 1: return '4';
      case 2: return '7';
      case 3: return '*';
      case 4: return '2';
      case 5: return '5';
      case 6: return '8';
      case 7: return '0';
      case 8: return '3';
      case 9: return '6';
      case 10: return '9';
      case 11: return '#';
      case 12: return 'A';
      case 13: return 'B';
      case 14: return 'C';
      case 15: return 'D';
    }
  }
}keypad;
