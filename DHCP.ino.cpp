#define LEFT 10
#define RIGHT 11
#define LED 7
#define SWITCH 2

#include <Wire.h>
//--------Libraries and external sources--------
#include <EEPROM.h>
#include <Wire.h>
#include <EEPROMextent.h>
#include <SoftwareSerial.h>

int SWITCHSTATE = 0;
//--------Variable Declaration--------
#define MASTER_ADDRESS 0x04;
#define SLAVE_ADDRESS 0x05;

int LEFTMOTOR() {
  digitalWrite(LEFT, HIGH);
  digitalWrite(RIGHT, LOW);
}
int number = 0;
int state = 0;
int address = 0; // the current address in the EEPROM
int rawpacket;

int RIGHTMOTOR(){
  digitalWrite(LEFT, LOW);
  digitalWrite(RIGHT, HIGH);
}
SoftwareSerial SERIAL(10, 11); // RX, TX

void setup(){
//---------------Setup---------------
void setup()

  pinMode(LEFT, OUTPUT);
  pinMode(RIGHT, OUTPUT);
  pinMode(LED, OUTPUT);  
//------------Opening Streams------------
  EEPROM.begin(512); // EEPROM is slow, such is life in flash memory.
  SERIAL.begin(115200); // Serial is fast, such is life on the internet super highway.

  pinMode(RIGHT, INPUT);
  pinMode(LED, INPUT); 
//-------------I2C-------------
//  Wire.begin(SLAVE_ADDRESS);
//  Wire.onReceive(receiveData);
//  Wire.onRequest(sendData);
//  Serial.println("I2C connection established with", MASTER_ADDRESS);

//-----------Motor Definition-----------
  digitalWrite(LEFT, LOW);
  digitalWrite(RIGHT, LOW);

//---------------EEPROM Set---------------

}
// Serial.print(settings.value1);

void loop(){
  delay(2000);

void loop() {

  SWITCHSTATE = digitalRead(SWITCH);{
  // callback for received data
//  void receiveData(int byteCount) {

  while(Wire.available()) {
    rawpacket = Wire.read();
    Serial.print("data received: ");
    Serial.println(rawpacket);
//    EEPROM.write

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

  LEFTMOTOR();
  RIGHTMOTOR();
}

// callback for sending data
//void sendData(){
//Wire.write(number);
}

def switch_demo(argument):
    switcher = {
        1: "Left",                 // Left Motor Only
        2: "Right",                // Right Motor Only
        3: "Fore",                 // Forward
        4: "Stop",                 // Stop
        5: "StopTalkingS",         // Cut Comms - Serial
        6: "StopTalkingII",        // Cut Comms - IIC

    }
    print switcher.get(argument, "Invalid month")