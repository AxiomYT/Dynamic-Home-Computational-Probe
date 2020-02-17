import serial

port = input("Please enter the port location - (`/dev/ttyUSB0`)"); # Asks for anticipated COM port

COSMIC2 = serial.Serial('port', 9600, timeout=5)  # open serial port

print(COSMIC2.name) # Checks what port was opened

# Function Definition.

def COMMAND(PINGSTAGE, TIME): # Function to send control command.
	
	if (time != 0): # If Time in seconds is not 0.
		
		COSMIC2.Serial(COMMAND + ".RESPOND," + TIME + "."); # Send command with time attached.
		
		time.sleep(1);

		receive ACK
			
			PINGSTAGE == ("ACK");
			
			return;
	
	else: # If Time is not specified. ( Most of the time. )
		
		COSMIC2.Serial(COMMAND + ".RESPOND,ASAP."); # Send Command with standard instant response.
		
		time.sleep(1);
			
			PINGSTAGE == ("ACK");
			
			return;
			
def DATA(): # Function to retrieve data.
	
	request (TEMP, LIGHT, HUMIDITY, FOREDISTANCE, SIDEDISTANCE);
	
	time.sleep(1);
	
	recieve (TEMP, LIGHT, HUMIDITY, FOREDISTANCE, SIDEDISTANCE);
	
	time.sleep(1);
	
	receive ACK

	return (TEMP, LIGHT, HUMIDITY, FOREDISTANCE, SIDEDISTANCE);

def CONTROL(CONTROL, VALUE, TIME):

	COSMIC2.Serial(CONTROL, VALUE, TIME);

	time.sleep(1);

	receive ACK

	return (ACK) # Function to send movement Data.