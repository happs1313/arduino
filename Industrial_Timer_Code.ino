#include <RTClib.h>
#include <LiquidCrystal.h>

#define LED 13
#define MODE A0
#define ENTER A1
#define DOWN A2
#define UP A3

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);



RTC_DS1307 RTC;
int HOUR, MINUT, SECOND;
int tim_pos=0;
bool mode = 0,alert=0;
int UP_button,DOWN_button,ENTER_button,MODE_button;
int STHOUR=1,STMIN=38,SPHOUR=1,SPMIN=39;


void setup() {
  pinMode(UP,INPUT_PULLUP);
  pinMode(DOWN,INPUT_PULLUP);
  pinMode(ENTER,INPUT_PULLUP);
  pinMode(MODE,INPUT_PULLUP);
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  lcd.begin(16,2);
  RTC.begin();
  RTC.adjust(DateTime(__DATE__, __TIME__));
  //RTC.adjust(DateTime(2022, 02, 17, 05, 51, 45));
  if (!RTC.isrunning())
  {
    //RTC.adjust(DateTime(__DATE__, __TIME__));
    
  }
  
}



void loop() {


  UP_button = digitalRead(UP);

  DOWN_button = digitalRead(DOWN);

  ENTER_button = digitalRead(ENTER);

  MODE_button = digitalRead(MODE);
  
  if(!MODE_button) mode=!mode; 



  DateTime now = RTC.now();
  HOUR = now.hour();
  MINUT = now.minute();
  SECOND = now.second();

  if(mode==0){   // Mode 0  =  ALARM MODE
    lcd.clear();
    
    lcd.setCursor(0,0); // 1st Line 1st Position
    lcd.print("S:");
    if(STHOUR/10==0) lcd.print("0");
    lcd.print(STHOUR);
    lcd.print(":");
    if(STMIN/10==0) lcd.print("0");
    lcd.print(STMIN);
    lcd.print(" ");
    lcd.print("E:");
    if(SPHOUR/10==0) lcd.print("0");
    lcd.print(SPHOUR);
    lcd.print(":");
    if(SPMIN/10==0) lcd.print("0");
    lcd.print(SPMIN);
    
    
    
    lcd.setCursor(0,1); // 2st Line 1st Position
    if(alert) lcd.print("ON");
    else lcd.print("OFF");
    lcd.print("  ");
    lcd.print("Now- ");
    if(HOUR/10==0) lcd.print("0");
    lcd.print(HOUR);
    lcd.print(":");
    if(MINUT/10==0) lcd.print("0");
    lcd.print(MINUT);
    
    
    if (STHOUR == HOUR && STMIN == MINUT) {
      digitalWrite(LED,HIGH);
      alert = true;
    }
    if (SPHOUR == HOUR && SPMIN == MINUT)  {
      digitalWrite(LED,LOW);
      alert = false;
    }
    
    delay(200);
  }
  
  if(mode==1){ // MODE 1 FOR TIMER SET

   lcd.clear();
    
    lcd.setCursor(0,0); // 1st Line 1st Position
    lcd.print("S:");
    if(STHOUR/10==0) lcd.print("0");
    lcd.print(STHOUR);
    lcd.print(":");
    if(STMIN/10==0) lcd.print("0");
    lcd.print(STMIN);
    lcd.print(" ");
    lcd.print("E:");
    if(SPHOUR/10==0) lcd.print("0");
    lcd.print(SPHOUR);
    lcd.print(":");
    if(SPMIN/10==0) lcd.print("0");
    lcd.print(SPMIN);
    
    
    
    lcd.setCursor(0,1); // 2st Line 1st Position
    lcd.print("SET TIMER MODE");
    UP_button = digitalRead(UP);
    DOWN_button = digitalRead(DOWN);
    ENTER_button = digitalRead(ENTER);
    
    

    if(!UP_button){
      switch (tim_pos){
        case 0:
          STHOUR++;
          if(STHOUR==25) STHOUR=0;
        break;
        case 1:
          STMIN++;
          if(STMIN==60) STMIN=0;
        break;
        case 2:
          SPHOUR++;
          if(SPHOUR==25) SPHOUR=0;
        break;
        case 3:
          SPMIN++;
          if(SPMIN==60) SPMIN=0;
        break;
      }
    } 
    if(!DOWN_button){
      switch (tim_pos){
        case 0:
          STHOUR--;
          if(STHOUR==-1) STHOUR=24;
        break;
        case 1:
          STMIN--;
          if(STMIN==-1) STMIN=59;
        break;
        case 2:
          SPHOUR--;
          if(SPHOUR==-1) SPHOUR=24;
        break;
        case 3:
          SPMIN--;
          if(SPMIN==-1) SPMIN=59;
        break;
      }
    }
    

    if(!ENTER_button){
      if(tim_pos == 3) tim_pos = 0;
      else tim_pos++;
    } 
    delay(200);
  }
  


}
