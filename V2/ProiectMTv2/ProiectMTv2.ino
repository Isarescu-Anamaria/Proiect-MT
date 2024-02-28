#include <avr/interrupt.h>

const int pinFotorezistor = A0;// Pinul analogic pentru fotorezistor
const int pinLED1 = 9;// Pin digital pentru LED1
const int pinLED2 = 10;// Pin digital pentru LED2
const int pinPIR = 12;// Pinul digital pentru senzorul PIR

const int pinButon = 2;
const int pinLED_rosu = 5;
const int pinLED_verde = 6;

volatile unsigned int timerCount = 0;
bool ledVerdeActive = false;

void setup() {
  // Setează pinul A0 ca intrare
  // portul C (pinii A0-A5)
  DDRC &= ~(1 << DDC0);
  // Setează pinii 9 si 10 ca ieșire
  // DDRB este registrul pentru configurarea pinilor
  DDRB |= (1 << DDB1);
  DDRB |= (1 << DDB2);
  // Setează pinul 12 ca intrare pentru senzorul PIR
  // Bitul 4 al registrului DDRB corespunde pinului 12
  DDRB &= ~(1 << DDB4);
  
  // Setează pinii 5 si 6 ca ieșire pentru semafor
  // DDRD este registrul pentru configurarea pinilor
  DDRD |= (1 << DDD5);
  DDRD |= (1 << DDD6);
  
  DDRD &= ~(1 << DDD2);//Setare pin pentru buton
  
  TCCR1B |= (1 << CS11) | (1 << CS10);
  //TCCR1B |= (1 << CS11); // Prescaler de 8
  TIMSK1 |= (1 << TOIE1);
  
  Serial.begin(9600);//Inițializează comunicarea serială
  
  sei();
}

void loop() {
  
  // Citeste valoarea analogica de pe pinul A0
  int valoareFotorezistor = analogRead(pinFotorezistor);
  // Citeste valoarea de la senzorul PIR
  int valoareSenzorPIR = digitalRead(pinPIR);
  int valoareButon = digitalRead(pinButon);
  
  Serial.print("Fotorezistor: ");
  Serial.println(valoareFotorezistor);
  Serial.print("PIR: ");
  Serial.println(valoareSenzorPIR);
  Serial.print("Buton: ");
  Serial.println(valoareButon);
  
  PORTD |= (1 << PORTD5); //aprindere LED rosu
  
  // Verifica valoarea analogica si controleaza LED-ul
  if (valoareFotorezistor <= 255) 
  {
    PORTB |= (1 << PORTB1);// Aprinde LED-ul 1
    PORTB |= (1 << PORTB2);// Aprinde LED-ul 2
    analogWrite(pinLED1, 255 - valoareFotorezistor);
    analogWrite(pinLED2, 255 - valoareFotorezistor);
    
  } else 
  {
    PORTB &= ~(1 << PORTB1);// Stinge LED-ul 1
    PORTB &= ~(1 << PORTB2);// Stinge LED-ul 2
  }
  
  if (valoareSenzorPIR == HIGH)
  {
    int val = 1.2 * (255 - valoareFotorezistor); 
    if (val <= 255)
    {
      analogWrite(pinLED1, val);
    }
  }
  else
  {
    analogWrite(pinLED1, 10000 / valoareFotorezistor); 
  }
  
  if (valoareButon == HIGH) {
    delay(50);
    if (digitalRead(pinButon) == HIGH) {
      timerCount = 0;
      ledVerdeActive = true;
    }
  }
  
  
  if (ledVerdeActive && timerCount >= 10000) 
  { 
    PORTD |= (1 << PORTD6); //aprindere LED verde
    PORTD &= ~(1 << PORTD5); // Stinge LED-ul rosu
  }
  
  if (ledVerdeActive && timerCount >= 20000)
  { 
    PORTD &= ~(1 << PORTD6); // Stinge LED-ul verde
    PORTD |= (1 << PORTD5); //aprindere LED rosu
    ledVerdeActive = false;  // Activează LED-ul verde
  }
  
  delay(100);  // Pauza de 100 de milisecunde
}

ISR(TIMER1_OVF_vect) 
{
  timerCount++;
}
