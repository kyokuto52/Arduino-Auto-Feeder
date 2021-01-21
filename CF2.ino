#include <Servo.h>
#include <Wire.h>
#include <time.h>
#include <ACROBOTIC_SSD1306.h>

Servo moto;

int sleepmin = 2;
int sleepmax = 9;

int count;
int h;
int m;
int s;
String h2;
String m2;
String s2;
time_t tt;
tm* dt;

bool starBlink;

void setup() {
  Wire.begin();
  oled.init(); 
  oled.clearDisplay();
  moto.attach(6);
  moto.write(25);
}

void loop() {
   refreshTime();
   refreshOLED();
   if(m == 0 && s == 0){
     if(h < sleepmin || h >= sleepmax){
      feed();
      count++;
     }
     delay(420);
   }else{
     delay(500);
   }
}

void feed(){
  moto.write(25);
  delay(80);
  moto.write(-15);
  delay(80);
  moto.write(25);
  delay(80);
  moto.write(-15);
  delay(80);
  moto.write(25);
  delay(80);
  moto.write(-15);
  delay(80);
  moto.write(25);
  delay(100);
}

void refreshOLED(){
  //StarBlink
  if(h < sleepmin || h >= sleepmax){
    if(starBlink){
      oled.setTextXY(1, 1);
      oled.putString("**");
      oled.setTextXY(2, 1);
      oled.putString("**");
      starBlink = false;
    }else{
      oled.setTextXY(1, 1);
      oled.putString("  ");
      oled.setTextXY(2, 1);
      oled.putString("  ");
      starBlink = true;
    }
  }else{
    oled.setTextXY(1, 1);
    oled.putString("  ");
    oled.setTextXY(2, 1);
    oled.putString("  ");
  }
  
  //Line1
  oled.setTextXY(0, 0);
  oled.putString("+--+");
  oled.setTextXY(0, 8);
  oled.putString(h2 +":" + m2 + ":" +s2);

  //Line2
  oled.setTextXY(1, 0);
  oled.putString("|");
  oled.setTextXY(1, 3);
  oled.putString("|");

  //Line3
  oled.setTextXY(2, 0);
  oled.putString("|");
  oled.setTextXY(2, 3);
  oled.putString("|");
  oled.setTextXY(2, 1);

  oled.setTextXY(2, 5);
  oled.putString("Times:" + String(count));

  //Line4
  oled.setTextXY(3, 0);
  oled.putString("+--+");

  oled.setTextXY(3, 5);
  oled.putString("Sleep:2H-9H");

  //Line5

  //Line6
  oled.setTextXY(5, 0);
  oled.putString("+--------------+");

  //Line7
  oled.setTextXY(6, 0);
  if(m<4)             {oled.putString("|*             |");}
  else if(m>=4&&m<8)  {oled.putString("|**            |");}
  else if(m>=8&&m<12) {oled.putString("|***           |");}
  else if(m>=12&&m<16){oled.putString("|****          |");}
  else if(m>=16&&m<20){oled.putString("|*****         |");}
  else if(m>=20&&m<24){oled.putString("|******        |");}
  else if(m>=24&&m<28){oled.putString("|*******       |");}
  else if(m>=32&&m<36){oled.putString("|********      |");}
  else if(m>=36&&m<40){oled.putString("|*********     |");}
  else if(m>=40&&m<44){oled.putString("|**********    |");}
  else if(m>=44&&m<48){oled.putString("|***********   |");}
  else if(m>=48&&m<52){oled.putString("|************  |");}
  else if(m>=52&&m<56){oled.putString("|************* |");}
  else                {oled.putString("|**************|");}

  //Line8
  oled.setTextXY(7, 0);
  oled.putString("+--------------+");
}

void refreshTime(){
   tt = time(NULL);
   dt = localtime(&tt);
   h = dt->tm_hour;
   m = dt->tm_min;
   s = dt->tm_sec;
   if(h<10){h2=" " + String(h);}
   else{h2=String(h);}
   if(m<10){m2=" " + String(m);}
   else{m2=String(m);}
   if(s<10){s2=" " + String(s);}
   else{s2=String(s);}
}
