#include<Ultrasonic.h>

Ultrasonic ultrasonic (A0, A1);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int v = ultrasonic.Ranging(CM);
  Serial.println(v);
  
  delay(1000);
}
