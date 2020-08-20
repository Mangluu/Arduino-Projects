#include<Ultrasonic.h> 


Ultrasonic ultrasonic(A0,A1);//Init an Ultrasonic object
// Distance;
void setup() {
Serial.begin(9600);
}

void loop()
{
int Distance=ultrasonic.Ranging(CM);//get the current result;
 delay(100);
 Serial.print("the distance is ");
 Serial.println(Distance);
 delay(1000);
}
