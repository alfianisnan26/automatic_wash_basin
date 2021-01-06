#include "basic.h"

DNB myDelay;
DNB timerSeq;
DNB ledKranBlink;

void setup() {
  Serial.begin(9600);
  //byte keypadPin[5] = {KEY_S,KEY_A,KEY_B,KEY_C,KEY_D};
  //keypad.init(keypadPin);
  myLCD.init();
  rtc.init();
  thermo.init();
  //myDelay.load(1000, true);
  //myLCD.welcome();
  //myLCD.getString.init();
  interface.servo.init();
  delay(2000);
  thermo.envi();
}

byte state = 0;
bool refresh = false;

void loop() {
  switch(state){
    case 0:{
      if(us.sabun.get()){
        pl("0|11 Sabun runs out");
        state = 11;
        ledKranBlink.load(1, true);
        myLCD.clear();
        myLCD.lcdpl(0,3, "Isi Ulang Sabun!");
      }
      else if(us.sink.get()){
        pl("0|1 A Man Detect");
        interface.led.cermin.on();
        ledKranBlink.load(3, true);
        myLCD.clear();
        myLCD.msg.welcome();
        state = 1;
        refresh = false;
      }else{
        
        if(!refresh){
          myLCD.clear();
          interface.servo.kran.close();
          interface.servo.sabun.close();
          interface.led.cermin.off();
          interface.led.kran.off();
          refresh = true;
          myLCD.lcdpl(0,2, "Automatic Washing");
          myLCD.lcdpl(0,3, "Basin");
          
          //................01234567890123456789......
        }
        rtc.showOnLCD(0);
      }
      break;
    }
    case 1:{
      if(!us.sink.get()){
        pl("1|0 A Man Has Gone");  
        myLCD.clear();
        state = 0;
      }else{
        if(us.kran.get()){
          pl("1|2 Man Hand under the kran");  
          myLCD.clear();
          myLCD.msg.basahi();
          state = 2;
          timerSeq.load(30, false);
          interface.servo.kran.open();
          interface.led.kran.off();
        }
        if(ledKranBlink.run()){
          interface.led.kran.toggle();
        }else{
          p("Timer LED Kran Blink : ");
          pl(ledKranBlink.count);
        }
      }
      break;
    }
    case 2:{
      if(!us.sink.get()){
        pl("2|10 Man has Gone, but sequence running");
        state = 10;
        myDelay.load(20, false);
      }else if(timerSeq.run()){
        state = 3;
        myLCD.clear();
        myLCD.msg.cutang();
        pl("2|3 Go to the sequence of Waiting Sabun");
        interface.servo.kran.close();
        interface.servo.sabun.open();
        timerSeq.load(20, false);
      }else{
        p("Timer Kran : ");
        pl(timerSeq.count);
      }
      break;
    }
    case 3:{
      if(timerSeq.run()){
        pl("3|4 Next to sequence of \"Menggosok Tangan\"");
        state = 4;
        timerSeq.load(300, false);
        thermo.body();
        interface.servo.sabun.close();
      }else{
        p("Timer Sabun : ");
        pl(timerSeq.count);
      }
      break;
    }
    case 4:{
      if(timerSeq.run()){
        if(us.kran.get()){
          myLCD.clear();
          pl("4|5 Next to sequence of \"Bilas membilas\"");
          state = 5;
          interface.servo.kran.open();
          myLCD.lcdpl(0,0, "Suhu Anda : ");
          myLCD.lcdpl(12,0, String(thermo.out)+"C");
          if(!thermo.lastRead){
            pl("Normal People");
            myLCD.lcdpl(0,3, "Suhu Anda Normal");
          }else{
            pl("Indicated to Positive Corona");
            interface.buzz();
            myLCD.lcdpl(0,2, "Suhu Diatas Normal");
            myLCD.lcdpl(0,3, "Mhn Periksa Ke Dokter");
          }
        }
      }else{
        p("Timer Menggosok : ");
        pl(timerSeq.count);
      }
      break;
    }
    case 5:{
      if(!us.kran.get()){
        interface.noBuzz();
        myLCD.clear();
        myLCD.lcdpl(0,2, "Terima kasih");
        myLCD.lcdpl(0,3, "Bersih sebagian iman");
        //................01234567890123456789
        pl("5|6 Sequence is finished");
        state = 6;
        interface.servo.kran.close();
      }
      break;
    }
    case 6:{
      if(!us.sink.get()){
        pl("6|0 Goodbye Statement");
        state = 0;
      }
      break;
    }
    case 10:{
      if(us.sink.get()){
        pl("10|2 Man is comebanck, returning to sequence");
      }else{
        if(myDelay.run()){
          pl("10|0 Man is really gone, sequence terminated");
          myDelay.clear();
          state = 0;
        }else{
          pl(myDelay.count);
        }
      }
      break;
    }
    case 11:{
      if(!us.sabun.get()){
        pl("11|0 sabun is refilled");
        state = 0;
        interface.led.sabun.off();
        refresh = false;
      }else{
        rtc.showOnLCD(0);
        if(ledKranBlink.run()) interface.led.sabun.toggle();
        else{
          p("Timer Sabun Blink : ");
          pl(ledKranBlink.count);
        }
        
      }
      break;
    }
  }
  //interface.led.sabun.toggle();
  //interface.servo.kran.toggle();
 //myLCD.keyNum();
 //rtc.showOnLCD(0);
 //if(myLCD.getString.waitInput()) pl(myLCD.getString.str);
 //thermo.body();
}
