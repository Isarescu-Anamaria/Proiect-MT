  int ir1=2;
  int ir2=3;
  int ir3=4;
  int ir4=5;
  int led1=6;
  int led2=7;
  int led3=8;
  int led4=9;
  int prox1=0;
  int prox2=0;
  int prox3=0;
  int prox4=0;

  int light = 0; // store the current light value
  int v1 = 0;
  int v2 = 0;

 void setup() {
     // put your setup code here, to run once:
    Serial.begin(9600); //configure   serial to talk to computer
     pinMode(A0, INPUT);
     pinMode(ir1,INPUT);
     pinMode(ir2,INPUT);
     pinMode(ir3,INPUT);
     pinMode(ir4,INPUT);
     pinMode(led1,OUTPUT);
     pinMode(led2,OUTPUT);
     pinMode(led3,OUTPUT);
     pinMode(led4,OUTPUT);
 }

    void   loop() {
    // put your main code here, to run repeatedly:
  
    light = analogRead(A0);   // read and save value from LDR
    
    Serial.println(light); // print current   light value
 
      v1= light; 
      v2= 450-v1;  

      prox1=digitalRead(ir1);
      prox2=digitalRead(ir2);
      prox3=digitalRead(ir3);
      prox4=digitalRead(ir4);

  if (light < 450)  //daca se intuneca se aprind led-urile in functie de intensitatea luminii
 {
    //led1
    digitalWrite(led1, HIGH); 
    delayMicroseconds(v2);   
    digitalWrite(led1, LOW);  
    delayMicroseconds(v1);
    //led2
    digitalWrite(led2, HIGH); 
    delayMicroseconds(v2);   
    digitalWrite(led2, LOW);  
    delayMicroseconds(v1);
    //led3
    digitalWrite(led3, HIGH); 
    delayMicroseconds(v2);   
    digitalWrite(led3, LOW);  
    delayMicroseconds(v1);
    //led4
    digitalWrite(led4, HIGH); 
    delayMicroseconds(v2);   
    digitalWrite(led4, LOW);  
    delayMicroseconds(v1);

    //setare senzori IR
    
  if(prox1==HIGH)
  {
    digitalWrite(led1, HIGH); 
    delayMicroseconds(v2 - 50);   
    digitalWrite(led1, LOW);  
    delayMicroseconds(v1 - 50);
    
  }
  else
  {
    digitalWrite(led1, HIGH); 
    delayMicroseconds(v2);   
    digitalWrite(led1, LOW);  
    delayMicroseconds(v1);
  }
  if(prox2==HIGH)
  {
    digitalWrite(led2, HIGH); 
    delayMicroseconds(v2 - 50);   
    digitalWrite(led2, LOW);  
    delayMicroseconds(v1 - 50);
    
  }
  else
  {
    digitalWrite(led2, HIGH); 
    delayMicroseconds(v2);   
    digitalWrite(led2, LOW);  
    delayMicroseconds(v1);
  }
  if(prox3==HIGH)
  {
    digitalWrite(led3, HIGH); 
    delayMicroseconds(v2 - 50);   
    digitalWrite(led3, LOW);  
    delayMicroseconds(v1 - 50);
  }

  else
  {
    digitalWrite(led3, HIGH); 
    delayMicroseconds(v2);   
    digitalWrite(led3, LOW);  
    delayMicroseconds(v1);
  }
  if(prox4==HIGH)
  {
    digitalWrite(led4, HIGH); 
    delayMicroseconds(v2 - 50);   
    digitalWrite(led4, LOW);  
    delayMicroseconds(v1 - 50);
  }
  else
  {
    digitalWrite(led4, HIGH); 
    delayMicroseconds(v2);   
    digitalWrite(led4, LOW);  
    delayMicroseconds(v1);
  }
 }
  
  if (light > 450)  // daca e lumina se sting led-urile
  {
          Serial.println("It   is quite light!");
          digitalWrite(6,LOW); //turn rigt LED off
          digitalWrite(7,LOW); // turn right LED off
          digitalWrite(8,LOW); //turn left LED off
          digitalWrite(9,LOW); //turn left LED off
  }
  
    //delay(1000); // don't spam the computer!
    
}
