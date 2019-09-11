# This code was written by Logan Tarvit https://www.github.com/AxiomYT
# All Variables written in all Capital letters, Function names and imported libraries written in CamelCase

# Code to note:
# Unlike SPI, I2C Relies on a set of addresses and registers. THis is because SPI is configured to talk to one chip at a time while I2C can share many
# devices on one bus. To avoid conflicts, addresses are assigned to devices ( by the manufacturer ) so that each one knows when the host ( The PI ) is
# Trying to talk to it. The address for our temperature sensor is probably 0x48, however if it is not, the code can easily be rectified.

# Each time we want to communicate with our device, we must send out it's address (0x48) on the bus. Only then can we send the address that we want to
# read or write from.

# //Importing Libraries\\

from Bluetin_Echo import Echo # Needed ultrasonic sensor library
from time import sleep # Needs to pause to wait for certain sensor data
import smbus # For Communicating over I2C
import time # Might need it at some point, it's always useful to have
import math # Same reason as above

# //Defining Variables\\

def SPEED_OF_SOUND = 315; # Can get a little funky if you screw with this - best not to.
def SAMPLES = 5; # Takes 5 samples of ultrasonic pulses and averages them to return a single value.

# I2C Send and Recieve Set Up

def I2C_CH = 1; # I2C Port 1
def I2C_ADDRESS = 0x48; # Temperature Sensors Address on the I2C Bus
def REG_TEMP = 0X00 # Register Address
def REG_CONFIG = 0X001 # Register Address

# Calculate the Two's compliment ( the first bit of the 12 bit number determines if the value is negative or positive, 0 for negative, 1 for positive.

def TWOS_COMP(val, bits): # Call to resolve a two's compliment data packet
    if (val & (1 << (1 << bits - 1))) ! = 0: # To convert a Two's compliment to a negative number we need to check the first bit, if it's 0 we just use the number as is
        val = val - (1 << bits) # However if it's a 1, we subtract the max negative number of the two's compliment ( 2^12 = 4096 in this case) from our number
    return val # Returns current value to Main programme

# Read Temperature

def READ_TEMP(): # Call to read temperature and returns as TEMPERATURE_C
    val = bus.read_i2c_block_data(I2C_ADDRESS, REG_TEMP, 2) # Reads temperature registers
    TEMPERATURE_C = (val[0] << 4 ) | (val[1] >> 5 ) # Temperature is in 12 bits, when reading the two bytes that contain the reading, we need to remove the last 4 bits from the second byte. We also move the first byte over 4 bits.
    TEMPERATURE_C = TWOS_COMP(TEMPERATURE_C, 12) # Converts to compliment (Temperature can be Negative)
    TEMPERATURE_C = TEMPERATURE_C * 0.0625 # Converts Registers Value to temperature (Celcius) Alse accounts for 0.0625 Resolution
    return TEMPERATURE_C # Returns TEMPERATURE_C to main programme

# Initialise I2C (SMBus)

    def BUS = smbus.SMBus(I2C_CH) # Sets bus channel as bus 1
    val = BUS.read_i2c_block_data(I2C_ADDRESS, REG_CONFIG, 2)# Reads the current CONFIG register (2 Bytes)
    print("Old CONFIG:", val) # Currently just prints

    val[1] = val[1] & 0b00111111 # Sets to 4Hz sampling
    val[1] = val[1] | (0b10 << 6) # ( CR1, CR0 = 0b10 )

    BUS.write_i2c_block_data(I2C_ADDRESS, REG_CONFIG, val) # Writes 4Hz sampling back to CONFIG

    val = BUS.read_i2c_block_data(I2C_ADDRESS, REG_CONFIG, 2) # Re-reads CONFIG to verify that we changed the value
    print("New CONFIG:", val) # Currently just prints

# Ultrasonic Sensor 1 - Front Firing
def HCSR04_1_PIN_TRIG 4 # Ultrasonic Sensor 1 / Ping Trigger
def HCSR04_1_PIN_ECHO 3 # Ultrasonic Sensor 1 / Ping Echo

# Ultrasonic Sensor 2 - Left Firing
def HCSR04_2_PIN_TRIG 6 # Ultrasonic Sensor 2 / Ping Trigger
def HCSR04_2_PIN_ECHO 5 # Ultrasonic Sensor 2 / Ping Echo

# Ultrasonic Sensor 3 - Right Firing
def HCSR04_3_PIN_TRIG 8 # Ultrasonic Sensor 3 / Ping Trigger
def HCSR04_3_PIN_ECHO 7 # Ultrasonic Sensor 3 / Ping Echo

# Ultrasonic Sensor 4 - Up Firing
def HCSR04_4_PIN_TRIG 10 # Ultrasonic Sensor 4 / Ping Trigger
def HCSR04_4_PIN_ECHO 9 # Ultrasonic Sensor 4 / Ping Echo

# Ultrasonic Sensor - Send and recieve all data
def HCSR04_ALL_ECHO = [Echo(HCSR04_1_PIN_TRIG, HCSR04_1_PIN_ECHO), # Contains a list of the commands
                       Echo(HCSR04_2_PIN_TRIG, HCSR04_2_PIN_ECHO), # in which to send to the
                       Echo(HCSR04_3_PIN_TRIG, HCSR04_3_PIN_ECHO), # ultrasonic library
                       Echo(HCSR04_4_PIN_TRIG, HCSR04_4_PIN_ECHO),] # to be parsed.

# Main Program
def main(); # Here we go!
    temperature = READ_TEMP() # Calls READ_TEMP and assigns it as temperature
    print(round(temperature, 2), "C") # Prints a celcius value rounded to 2 Significant figures
    time.sleep(0.1) # Pauses for a quick breath
    for counter in range(1, 6): # Please merciful god no more than 6 ultrasonic sensors
        for counter2 in range(0, len(HCSR04_ALL_ECHO)): # Counts the amount of sensors in HCSR04_ALL_ECHO and then revolves between all 4.
            result = HCSR04_ALL_ECHO{counter2].read('cm', 3) # Collates the result of sensor pings
            print('Sensor {} - {} cm'.format(counter2, round(result, 2))) # Prints sensor data
    echo[0].stop() # Reset GPIO Pins

# Loop
if __name__ == '__main__': # Very simple loop, can be
    main()                 # modified.
            
