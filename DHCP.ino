#define LEFT 10
#define RIGHT 11
#define LED 7
#define SWITCH 2

#include <Wire.h>
#include <EEPROM.h>

int SWITCHSTATE = 0;

int LEFTMOTOR() {
  digitalWrite(LEFT, HIGH);
  digitalWrite(RIGHT, LOW);
}

int RIGHTMOTOR(){
  digitalWrite(LEFT, LOW);
  digitalWrite(RIGHT, HIGH);
}

void setup(){
  
  pinMode(LEFT, OUTPUT);
  pinMode(RIGHT, OUTPUT);
  pinMode(LED, OUTPUT);  

  pinMode(RIGHT, INPUT);
  pinMode(LED, INPUT); 

  digitalWrite(LEFT, LOW);
  digitalWrite(RIGHT, LOW);



}

void loop(){
  delay(2000);
  
  SWITCHSTATE = digitalRead(SWITCH);{

   if (SWITCHSTATE == HIGH) {
    LEFTMOTOR();
    RIGHTMOTOR();
   } 
   else {
    
  }
  
  LEFTMOTOR();
  RIGHTMOTOR();
}

}
