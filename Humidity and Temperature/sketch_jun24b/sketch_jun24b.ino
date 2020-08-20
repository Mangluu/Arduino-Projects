#include <dht.h>
#include<Ultrasonic.h>
#include <Ubidots_Arduino_GPRS.h>
#include <sim900.h>
#include <GPRS_Shield_Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal.h>

const int rs = 10, en = 9, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Ultrasonic ultrasonic (A1, A2);

Ultrasonic garbage (A4, A5);
char data;
dht DHT;



#define dht_apin A1
#define PIN_TX    12    /* rx of Arduino (connect tx of gprs to this pin) */
#define PIN_RX    13   /* tx of Arduino (connect rx of gprs to this pin) */
#define BAUDRATE  9600
#define PHONE_NUMBER "9410432344"
#define MESSAGE_LENGTH 160
char message[MESSAGE_LENGTH]; /* buffer for storing message */
char phone[16];         /* buffer for storing phone number */
char datetime[24];        /* buffer for storing phone number */
int8_t messageIndex = 0;

GPRS Sim900_test(PIN_TX,PIN_RX,BAUDRATE); 


void setup(){
  
  Serial.begin(9600);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(A0, INPUT);
  pinMode(11,OUTPUT);
  pinMode(A3,OUTPUT);
  lcd.setCursor(0, 0); // top left
  lcd.begin(16, 2);
 
}
 
void loop(){

if(Serial.available()>0) {
  

  int v = ultrasonic.Ranging(CM);
  int g = garbage.Ranging(CM);

  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  
   DHT.read11(A0);
   data=Serial.read();
   Serial.print(data);
    
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
    
    if(data=='A')
    {
     digitalWrite(11, HIGH); 
    }
    
    else if(data=='B')
    {
      
    digitalWrite(11, LOW);
    }

      if(v<5)
      {
        for(int i=0;i<5;i++)
        {
          analogWrite(A3,HIGH);
          delay(2000);
          analogWrite(A3,LOW);
          delay(1000);
        }
      
      
      Sim900_test.callUp(PHONE_NUMBER); /* Call */
//        delay(25000);
        Sim900_test.hangup(); /* Hang up the call */
        int8_t count = 0;
        messageIndex = Sim900_test.isSMSunread(); /* Check if new message available */
              while( (messageIndex < 1) && !strstr( message,"Stop") )  /* No new unread message */
              {
                  if(count == 5)
                  {
                      messageIndex = Sim900_test.isSMSunread();
                      break;
                  }
                  count++;
                  delay(5000);
                  messageIndex = Sim900_test.isSMSunread();
              }
              while(messageIndex > 0 )  /* New unread message available */
              {
                  Sim900_test.readSMS(messageIndex, message, MESSAGE_LENGTH, phone, datetime);  /* Read message */
                    if(strstr( message,"Stop"))
                    {
                        Serial.println("Turning fan ON");
                        digitalWrite(4, LOW);
                        memset(message, 0, 160);
                    }
                  messageIndex = Sim900_test.isSMSunread();
              }         
        delay(10000);
    }
    
    if(g<3)
    {
      lcd.print("CLEAR GARBAGE"); 
    }
    else
    {
      lcd.print("NO GARBAGE"); 
    }

} 

 
}
