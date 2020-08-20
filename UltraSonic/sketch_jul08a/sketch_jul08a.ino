#include <HCSR04.h>



#include<Ultrasonic.h>

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  int v = Ultrasonic.Ranging(cm);
  Serial.print(v);
}
