//--------Libraries and external sources--------\\
#include <EEPROM.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Wire.h>

//--------Variable Declaration--------\\
#define MASTER_ADDRESS 0x04;
#define SLAVE_ADDRESS 0x05;

#define LEFT 10
#define RIGHT 11
#define LED 7
#define SWITCH 2

int SECS = 0;
int number = 0;
int state = 0;
int rawpacket;
int addr = 0;
int val = analogRead(0) / 4;

//----------Functions----------\\
int LEFTMOTOR(SECS) {
  digitalWrite(LEFT, LOW);
  digitalWrite(RIGHT, HIGH);
  delay(SECS);
  digitalWrite(RIGHT, LOW);
}

int RIGHTMOTOR(SECS) {
  digitalWrite(RIGHT, LOW);
  digitalWrite(LEFT, HIGH);
  delay(SECS);
  digitalWrite(LEFT, LOW);
}

void setup() {
//---------------Setup---------------\\

  pinMode(LEFT, OUTPUT);
  pinMode(RIGHT, OUTPUT);
  pinMode(LED, OUTPUT);  
//------------Opening Streams------------\\
//  EEPROM.begin(512); // EEPROM is slow, such is life in flash memory.
  Serial.begin(115200); // Serial is fast, such is life on the internet super highway.

  pinMode(RIGHT, INPUT);
  pinMode(LED, INPUT); 
//-------------I2C-------------\\
//  Wire.begin(SLAVE_ADDRESS);
//  Wire.onReceive(receiveData);
//  Wire.onRequest(sendData);
//  Serial.println("I2C connection established with", MASTER_ADDRESS);

//-----------Motor Definition-----------\\
  digitalWrite(LEFT, LOW);
  digitalWrite(RIGHT, LOW);

//---------------EEPROM Set---------------\\

}
// Serial.print(settings.value1);

void loop() {

  while(Wire.available()) {
    
    rawpacket = Wire.read();
    Serial.print("data received: ");
    Serial.println(rawpacket);
    EEPROM.write(addr, val);

   if (SWITCHSTATE == HIGH) {
    LEFTMOTOR();
    RIGHTMOTOR();
   } 
   else {
    if (number == 1) {

      if (state == 0) {
       digitalWrite(13, HIGH); // set the LED on
       state = 1;
     }

     else {
       digitalWrite(13, LOW); // set the LED off
       state = 0;
     }

    }
    else {

    }

  }

  FORWARD();
}

// callback for sending data
//void sendData(){
//Wire.write(number);
}
}
