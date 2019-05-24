# This file contains the code to write the collected data to a text file.
# This data will then be processed into JSON and sent via TCP to the 
# Driver Training Portal API.

# Run "pip install pyserial"
from serial import Serial

# There should be a function that loads the Arduino using arduino-mv
# so that there is command line functionality that can upload the sketch
# and begin the data collection process.

# Sets the serial port. To discover the name o fthe serial port, look at the
# the bottom of the Arduino IDE. This will depend on the name of the port for
# the Raspberry Pi.
ser = Serial('/dev/cu.usbmodem141101', 9600, 8, 'N', 1, timeout=5)
record = open('test_2.txt', 'w+') # This writes to a file that exists or opens a new file and writes the data.

# Write a function that calls a wait before collecting data, to ensure that the
# correct data is being processed. Also, make sure to code so that if there is an
# error, it is handled and the collection process continues

# This will be a function 
# def recordInfoToFile:
while True:
    if ser.in_waiting > 0:
        print(ser.readline())
        record.write(ser.readline().decode("utf-8"))
        
# Set up some sort of counter or some mechanism that determines when to close the file.
# This will probably be a hook that functions off of receiving the "Stop Collecting" signal
# from the Raspberry Pi.
record.close()     