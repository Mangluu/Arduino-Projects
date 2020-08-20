void setup() {
  // put your setup code here, to run once:
 pinMode(5, OUTPUT); 
 pinMode(6, OUTPUT); 
 pinMode(11, OUTPUT); 
}
void loop() {
  // put your main code here, to run repeatedly:
 for(int i=0;i<2;i++)
 {
  for(int j=0; j<2;j++)
  
    {
  
    if(j==1)
    {
      digitalWrite(6,HIGH);
     
    }
    else if(j==0)
    {
       digitalWrite(10,HIGH);
      
    }
    delay(2000);
  }
  
  
   if(i==1)
  {
     digitalWrite(11,HIGH);
      
  }
  else if(i==0)
  {
     digitalWrite(1,HIGH);
      
  }
  delay(2000);
 
 }
}

  
  
