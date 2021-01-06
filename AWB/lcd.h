#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20,20,4);

#define INCR 0
#define DECR 2
#define INCRAUTO 1
#define DECRAUTO 3

class VAL{
  public:
  int val = 0;
  int minVal = 0;
  int maxVal = 10;
  void set(const int x,const int y,const int z){
    val = x;
    minVal = y;
    maxVal = z;
  }
  bool load(byte state){
    if((state<DECR)?(val<maxVal):(val>minVal)){
      if(state<DECR)val++;
      else val--;
      return true;
    }
    else if((state == INCRAUTO && val >= maxVal) || (state == DECRAUTO && val <= minVal)){
      val =(state<DECR)?minVal:maxVal;
      return true;
    }
    else return false;
  }
};

class STRINPUT{
  char last_input;
  byte len = 0;
  byte chnum = 0;
  byte kind = 0; //0 - uppercase ; 1 - lowercase ; 2 - number
  bool toTrig = true;

  char toChar(const char start, const char maximum, byte type){
    char forOut = start + chnum;
    if(type == 1) forOut += 0x20;
    chnum++;
    if(chnum >= maximum) chnum = 0;
    return forOut;
  }

  void showKind(const int kindOf){
    lcd.noBlink();
    lcd.noCursor();
    lcd.setCursor(0,3);
    String output;
    switch(kindOf){
      case 1: output = "A - Lowercase"; break;
      case 0: output = "A - Uppercase"; break;
      case 2: output = "A - Numeric  "; break;
    }
    lcd.print(output);
    pl(output);
    lcd.setCursor(len, 0);
    lcd.blink();
  }

  DNB timeout;
  
  public:
  void init(){
    last_input = NULL;
    len = 0;
    chnum = 0;
    kind = 0; //0 - uppercase ; 1 - lowercase ; 2 - number
    toTrig = true;
    showKind(kind);
  }
  char str[21] = "";
  bool waitInput(){
    timeout.run();
    if(keypad.check() && keypad.isBuff){
      char ret = keypad.toChar();
      if((ret == '0' && kind!=2) || ret == '*' || ret == '#' || ret == 'A'){
        switch(ret){
          case '0':{
            lcd.setCursor(len, 0);
            lcd.print(' ');
            str[len] = ' ';
            len++;
            chnum = 0;
            if(len>19) len = 19;
            break;
          }
          case '*':{
            len--;
            chnum = 0;
            if(len<0 || len>19){
              len = 0;
              break;
            }
            lcd.setCursor(len, 0);
            lcd.print(' ');
            lcd.setCursor(len, 0);
            break;
          }
          case '#':{
            str[len] = '\0';
            len = 0;
            lcd.noCursor();
            lcd.blink();
            return true;
          }
          case 'A':{
            kind++;
            if(kind>=3) kind = 0;
            showKind(kind);
            break;
          }
        }
        last_input = NULL;
        timeout.clear();
        lcd.noCursor();
        lcd.blink();
      }else if(kind == 2 && ret != ret != 'B' && ret != 'C' && ret != 'D'){
        lcd.print(ret);
        str[len] = ret;
        len++;
        chnum = 0;
      }
      else if(ret!= 'B' && ret != 'C' && ret!= 'D' && len>= 0 && len<=19){
        if(last_input != ret){//generate new
          chnum = 0;
          len++;
          lcd.setCursor(len-1,0);
          if(timeout.state){
            lcd.cursor();
            lcd.noBlink();
          }
        }
        timeout.load(1000, false);
        char buff;
        switch(ret){
          case '1': buff = (kind == 0)?toChar('!', 7, 0):toChar('\'',8,0); break;
          case '2': buff = toChar('A', 3, kind); break;
          case '3': buff = toChar('D', 3, kind); break;
          case '4': buff = toChar('G', 3, kind); break;
          case '5': buff = toChar('J', 3, kind); break;
          case '6': buff = toChar('M', 3, kind); break;
          case '7': buff = toChar('P', 4, kind); break;
          case '8': buff = toChar('T', 3, kind); break;
          case '9': buff = toChar('W', 4, kind); break;
        }
        lcd.print(buff);
        lcd.setCursor(len-1,0);
        str[len-1] = buff;
      }
      last_input = ret;
    }
    if(timeout.hasData() && timeout.state){
      lcd.setCursor(len,0);
      lcd.blink();
      lcd.noCursor();
      last_input = NULL;
    }
    return false;
  }
};

class MSG{
  static void lcdp(const byte x, const byte y, const char* ch){
    lcd.setCursor(x,y);
    lcd.print(ch);
  }
  public:
  static void cutang(){
    lcdp(0,3, "Mencuci Tangan");
  }
  static void basahi(){
    lcdp(0,3, "Basahi tangan anda");
  }
  static void welcome(){
    lcdp(0,0, "Selamat Datang");
    lcdp(0,1, "Untuk mencuci tangan");
    lcdp(0,2, "letakkan tangan anda");
    lcdp(0,3, "dibawah kran");
    //.........01234567890123456789..........
  }
};

class LCD{
  VAL col;
  VAL row;
  public:
  void lcdp(const char ch){
    lcd.setCursor(col.val, row.val);
    lcd.print(ch);
  }
  void lcds(){
    lcd.setCursor(col.val, row.val);
  }
  void lcdpl(int x, int y, String str){
    lcd.setCursor(x, y);
    lcd.print(str);
    this->col.val = x;
    this->row.val = y;
  }
  void lcdc(){
    lcd.clear();
    this->col.val = 0;
    this->row.val = 0;
  }
  void clear(){lcd.clear();}
  static MSG msg;
  STRINPUT getString;
  void init(){ //LCD INIT
    col.set(0,0,19);
    row.set(0,0,3);
    lcd.begin(20, 4);                    
    lcd.backlight();
            //"...................."
    pl("LCD Initialized");
  }
  void welcome(){
    lcdc();
            //"...................."
    lcdpl(0,3,"Complete     Welcome");
    d(1000);
    lcdc();
    d(100);
    lcd.blink();
    d(100);
  }
  
  void keyNum(){
    if(keypad.check() && keypad.isBuff){
      char input = keypad.toChar();
      if(input == '*'){
        if(col.load(DECR)){
          lcdp(' ');
          lcds();
        }
      }
      else if(input == '#'){
        row.load(INCRAUTO);
        col.val = 0;
        lcds();
      }
      else{
        lcdp(input);
        if(!col.load(INCR)){
          row.load(INCRAUTO);
          col.val = 0;
          lcds();
        }
      }
    } 
  }
}myLCD;
