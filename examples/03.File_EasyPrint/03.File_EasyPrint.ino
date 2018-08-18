/*
  SD card read/write

 This example shows how to read and write data to and from an SD card file
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

#include <SPI.h>
#include <SD.h>
#include <TridentTD_EasyPrint.h>

File myFile;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial  << "Initializing SD card...";

  if (!SD.begin(4)) {
    Serial << "initialization failed!" <<endl;
    return;
  }
  Serial << "initialization done." <<endl;

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial << "Writing to test.txt...";
    myFile << "testing 1, 2, 3." << endl;       // ใช้ print ตามแบบ C++ Style
    // close the file:
    myFile.close();
    Serial << "done." <<endl;
  } else {
    // if the file didn't open, print an error:
    Serial << "error opening test.txt" <<endl;
  }

  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial << "test.txt:" <<endl;

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial << "error opening test.txt" <<endl;
  }
}

void loop() {
  // nothing happens after setup
}

