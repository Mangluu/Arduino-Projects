#include <dht.h>
#include<Ultrasonic.h>
#include <LiquidCrystal.h>

char data;
dht DHT;

const int rs = 10, en = 9, d4 = 5, d5 = 12, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Ultrasonic garbage (A1, A2);

Ultrasonic ultrasonic (A5, A4);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(11,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(A0, INPUT);
  pinMode(13,OUTPUT);
  lcd.setCursor(0, 0); // top left
  lcd.print("NOT FULL");
}

void loop() {
  // put your main code here, to run repeatedly:
  
  int v = ultrasonic.Ranging(CM);
  int g = garbage.Ranging(CM);
  
  if(Serial.available()>0)
  {
    data=Serial.read();
    Serial.print(data);
    
    if(data=='A')
    {
       digitalWrite(11, HIGH);
    }
   
    else if(data=='B')
    {
      digitalWrite(11, LOW);
    }
    
    DHT.read11(A0);

    if(DHT.temperature>28.00||data=='C')
    {
      
      digitalWrite(7,HIGH);
      digitalWrite(6,LOW);
      
    }
    
    else if (data=='D'||DHT.temperature<20.00)
    {
      
      digitalWrite(6,HIGH);
      digitalWrite(7,LOW);
    }


   
    
    
      }
  Serial.println(v);
  if(v<5)
      {
//       delay(2000);
        for(int i=0;i<5;i++)
        {
          digitalWrite(13,HIGH);
          delay(200);
          digitalWrite(13,LOW);
          delay(100);
        }

      }

  Serial.println(g);
  delay(1000);
         if(g<5)
    {
      lcd.begin(16, 2);
      lcd.print("FULL"); 
    }
    else
    {
      lcd.begin(16, 2);
      lcd.print("NOT FULL"); 
    }


}
