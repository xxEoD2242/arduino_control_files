// This file is a test to see if the SD card works properly

#include <SD.h>

const int chipSelect = 10;

String filename = "test_1.txt";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  while(!Serial){
    ; // Do nothing until serial is initialized
  }

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
}

void loop() {
  // put your main code here, to run repeatedly:
  File dataFile = SD.open(filename);

  if(dataFile) {
    // Get the size of the file before writing
    Serail.print("The file size is:");
    Serial.print(SD.size(filename));

    
    while (dataFile.available()) {
      Serial.write(dataFile.read());
    }
    // close the file:
    dataFile.close();
  }
  else {
    Serial.println("File failed to open!!");
  }
}
