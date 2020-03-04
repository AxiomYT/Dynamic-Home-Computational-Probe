//--------Libraries and external sources--------\\
#include <EEPROM.h>
#include <Wire.h>
#include <EEPROMextent.h>
#include <C:\Users\Logan\Documents\Arduino\libraries\SoftwareSerial-master\SoftwareSerial.h>

//--------Variable Declaration--------\\
#define MASTER_ADDRESS 0x04;
#define SLAVE_ADDRESS 0x05;

int number = 0;
int state = 0;
int address = 0; // the current address in the EEPROM
int rawpacket;

SoftwareSerial SERIAL(10, 11); // RX, TX

//---------------Setup---------------\\
void setup()
  
//------------Opening Streams------------\\
//  EEPROM.begin(512); // EEPROM is slow, such is life in flash memory.
  SERIAL.begin(115200); // Serial is fast, such is life on the internet super highway.

//-------------I2C-------------\\
//  Wire.begin(SLAVE_ADDRESS);
//  Wire.onReceive(receiveData);
//  Wire.onRequest(sendData);
//  Serial.println("I2C connection established with", MASTER_ADDRESS);
  
//-----------Motor Definition-----------\\


//---------------EEPROM Set---------------\\


// Serial.print(settings.value1);


void loop() {
  
  // callback for received data
//  void receiveData(int byteCount) {

  while(Wire.available()) {
    rawpacket = Wire.read();
    Serial.print("data received: ");
    Serial.println(rawpacket);
//    EEPROM.write

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
  
// callback for sending data
//void sendData(){
//Wire.write(number);
}
