#include <dht.h>
#include <Ubidots_Arduino_GPRS.h>
#include <sim900.h>
#include <GPRS_Shield_Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

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
dht DHT;
/* Create an object named Sim900_test of the class GPRS */
GPRS Sim900_test(PIN_TX,PIN_RX,BAUDRATE); 

//const int8_t lm35_pin = A1;

void setup() {
  Serial.begin(9600); /* Define baud rate for serial communication */
  pinMode(4, OUTPUT);     
  while(!Sim900_test.init())  /* Sim card and signal check, also check if module connected */ 
  {
      delay(1000);
      Serial.println("SIM900 initialization error");
  }  
  Serial.println("SIM900 initialization success");
  memset(message, 0, 160);
}

void loop() {
  
  
  
  
    if(temp_val>0)
    {
        Serial.println("Need to cool down");
        Serial.println("Calling to inform");
        Sim900_test.callUp(PHONE_NUMBER); /* Call */
        delay(25000);
        Sim900_test.hangup(); /* Hang up the call */
        int8_t count = 0;
        messageIndex = Sim900_test.isSMSunread(); /* Check if new message available */
              while( (messageIndex < 1) && !strstr( message,"Cool down") )  /* No new unread message */
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
                    if(strstr( message,"Cool down"))
                    {
                        Serial.println("Turning fan ON");
                        digitalWrite(4, HIGH);
                        memset(message, 0, 160);
                    }
                  messageIndex = Sim900_test.isSMSunread();
              }         
        delay(10000);
    }
    else
    {
        Serial.println("Everything is fine");
        digitalWrite(4, LOW); 
    }
  delay(3000);
}
