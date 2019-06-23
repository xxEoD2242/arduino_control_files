 // This file contains the start-up code, sampling instructions and general use cases for the GY-521
// IMU device. The connection between the Arduino and the IMU is made using I2C. 

// Created: 18 May 2019
// Updated: 
// Version Number: 1.0

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
// #include <utility/imumaths.h>
// #include <math.h>
#include <SD.h>

Adafruit_BNO055 bno = Adafruit_BNO055(28);

const int chipSelect = 10;

//*********************************** SD CARD PRESETUP ************************

char filename[] = "meas_00.txt";
void increment_filename(char[]);

void setup() {

  // Open serial communications and wait for port to open
  Serial.begin(9600);
  while(!Serial) {
    ; // Wait for serial port to connect
  }

  if(!bno.begin())
  {
    Serial.print("Ooops, no BN0055 detected --- Check your wiring or I2C address!");
    while(1);
  }

  delay(1000);

  bno.setExtCrystalUse(true);

  // ******************************* SD CARD SETUP ***********************************
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");

  // Check if a previous file existed. If it does, then increment the next file name
  // Increment the file name
  Serial.println(filename);
  while (SD.exists(filename)) {
    increment_filename(filename);
    Serial.print("The new filename is: ");
    Serial.println(filename);
  }

  // Inform the user that data is being logged.
  Serial.println("Begin logging data");
}

void loop() {
  
  imu::Vector<3> linear_accel = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  imu::Vector<3> angular_veloc = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  
  // ************************* CONVERT DATA FOR SD WRITE **************************
  
  // IMU CONVERSION
  String acceleration_of_x = String(linear_accel.x());
  String acceleration_of_y = String(linear_accel.y());
  String acceleration_of_z = String(linear_accel.z());
  String angular_of_x = String(angular_veloc.x());
  String angular_of_y = String(angular_veloc.y());
  String angular_of_z = String(angular_veloc.z());
  // String convert_temp = (temperature/340.00)+36.53;

  String imu_label = "IMU";
  String ax_label = "aX";
  String ay_label = "aY";
  String az_label = "aZ";
  String gx_label = "gX";
  String gy_label = "gY";
  String gz_label = "gZ";

  // Set up data string for entry onto SD card
  String dataString = "";

  dataString = "{"+imu_label+":{"+ax_label+": " + acceleration_of_x + ", " + ay_label + ": "+ acceleration_of_y + ", "+ az_label+": " + acceleration_of_z + ", "+ gx_label +": "+ angular_of_x +", "+ gy_label +":"+ angular_of_y +", "+ gz_label +": "+ angular_of_z +" }}";
  
  // Serial.println(dataString);

  // Record data to the SD Card file
  // Open file to save collected data
  File dataFile = SD.open(filename, FILE_WRITE);

  if(dataFile) {
    dataFile.println(dataString);
    dataFile.close();
  }
  else {
    Serial.println("File failed to open!!");
  }
  
  // This sets the number of times that data is read.
  // Currently, this is 10 Hz
  delay(100);
} // main

// This function increments the filename to ensure that any previously existing record files
// will not be overwritten until they are transferred to the databse.
//
// Return Type: void
//
// Variables:
//    filename  -Character Array- The filename of the file that is stored on the SD card

void increment_filename(char filename[])
{
  int updated_ones;
  int updated_tens;
  
  int tens_place = filename[5];
  int ones_place = filename[6];

  if(ones_place == 9)
  {
    updated_ones = ones_place + 1;
    updated_tens = tens_place + 1;
    filename[5] = updated_tens;
    filename[6] = updated_ones;
  }
  else
  {
    updated_ones = ones_place + 1;
    filename[6] = updated_ones;
  }
} // increment_filename
