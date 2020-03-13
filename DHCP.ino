//--------Libraries and external sources--------
#include <EEPROM.h>
#include <Wire.h>
#include <EEPROMextent.h>
#include <SoftwareSerial.h>
#include <stdint.h>
#include <Wire.h>

typedef void (*command)();

//--------Variable Declaration--------
#define EEPROM_BAUD_RATE 0x200
#define SERIAL_BAUD_RATE 0x1C200
#define MASTER_ADDRESS 0x04
#define SLAVE_ADDRESS 0x05

#define MEMORY_LOW 0x0
#define MEMORY_HIGH 0x64
#define DELAY 0x7D0

class Prom { // EEPROM Object
	public:
		uint16_t address;
		Prom() {
			address = MASTER_ADDRESS;
		}
}

//-------------Pin Declaration-------------

#define LEFT 10
#define RIGHT 11
#define LED 7
#define SWITCH 2

//-----------Function Declaration-----------

int LEFTMOTOR() {
	digitalWrite(LEFT, HIGH);
	digitalWrite(RIGHT, LOW);
}

int RIGHTMOTOR() {
	digitalWrite(LEFT, LOW);
	digitalWrite(RIGHT, HIGH);
}

int FORWARD() {
	RIGHTMOTOR();
	LEFTMOTOR();
}

int STOP() {
	digitalWrite(LEFT, LOW);
	digitalWrite(RIGHT, LOW);
}

int SERIALSTOP() {
	Serial.end();
}

int DATASTOP() {
	Wire.endTransmission();

	if (!Serial){
		Println("\n\nIIC Communication Halted.\n")
	}
}

void setup() {
//---------------Setup---------------
	Prom prom();
	EEPROMextent.clear(MEMORY_LOW, MEMORY_HIGH);

	pinMode(LEFT, OUTPUT);
	pinMode(RIGHT, OUTPUT);
	pinMode(LED, OUTPUT);  

//------------Opening Streams------------
	EEPROM.begin(EEPROM_BAUD_RATE); // EEPROM is slow, such is life in flash memory.
	SERIAL.begin(SERIAL_BAUD_RATE); // Serial is fast, such is life on the internet super highway.

	pinMode(RIGHT, INPUT);
	pinMode(LED, INPUT); 

//-------------I2C-------------
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
  Serial.println("I2C connection established with", MASTER_ADDRESS);

//-----------Motor Definition-----------
	digitalWrite(LEFT, LOW);
	digitalWrite(RIGHT, LOW);

//---------------EEPROM Set---------------

}
// Serial.print(settings.value1);

void loop(){
	delay(DELAY);
	while(Wire.available()) {
		rawpacket = Wire.read();
		Serial.print("data received: ");
		Serial.println(rawpacket);
    EEPROM.write(1);

	}

	command cmd = NULL;
	switch {
	case 1:
		cmd = LEFTMOTOR();
		break;
	case 2:
		cmd = RIGHTMOTOR();
		break;
	case 3:
		cmd = FORWARD();
		break;
	case 4:
		cmd = STOP();
		break;
	case 5:
		cmd = SERIALSTOP();
		break;
	case 6:
		cmd = DATASTOP();
		break;
	default:
		Serial.println("Error :(");
		return;
	}

	cmd();

}