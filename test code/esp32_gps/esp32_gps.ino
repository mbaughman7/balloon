/*
  Reading Lat/Long from the Qwiic GPS module over I2C
  By: Nathan Seidle
  SparkFun Electronics
  Date: April 12th, 2017
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  This example shows date, time and location.

  You will need two libraries:
  1) Use library manager to search for and install: 'SparkFun I2C GPS Arduino Library'
  2) Download and install the zip library from https://github.com/mikalhart/TinyGPSPlus

  The TitanX1 has a buffer of approximately 1,000 NMEA characters. If you don't poll the module
  for a few seconds this buffer will fill up. The first time you read from the GPS module you will
  receive this large buffer and may take up to 800ms to clear out the contents. After that it will
  take approximately 20ms to read the contents of the I2C buffer from the module.

  Hardware Connections:
  Attach a Qwiic shield to your RedBoard or Uno.
  Plug the Qwiic sensor into any port.
  Serial.print it out at 115200 baud to serial monitor.
*/

#include <SparkFun_I2C_GPS_Arduino_Library.h>  //Use Library Manager or download here: https://github.com/sparkfun/SparkFun_I2C_GPS_Arduino_Library
#include <TinyGPS++.h>                         //From: https://github.com/mikalhart/TinyGPSPlus
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
I2CGPS myI2CGPS;  //Hook object to the library
TinyGPSPlus gps;  //Declare gps object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


void setup() {
  Serial.begin(115200);
  Serial.println("esp32 with screen and gps");
  Wire.begin(5, 4);
  if (myI2CGPS.begin() == false) {
    Serial.println("Module failed to respond. Please check wiring.");
    while (1)
      ;  //Freeze!
  }
  Serial.println("GPS module found!");
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  startupText();
}

void loop() {
  while (myI2CGPS.available())  //available() returns the number of new bytes available from the GPS module
  {
    gps.encode(myI2CGPS.read());  //Feed the GPS parser
  }

  if (gps.time.isUpdated())  //Check to see if new GPS info is available
  {
    displayInfo();
  }
}

//Display new GPS info
void displayInfo() {
  //We have new GPS data to deal with!
  Serial.println();

  if (gps.time.isValid()) {
    Serial.print(F("Date: "));
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());

    Serial.print((" Time: "));
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());

    Serial.println();  //Done printing time
  } else {
    Serial.println(F("Time not yet valid"));
  }

  if (gps.location.isValid()) {
    Serial.print("Location: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(", "));
    Serial.print(gps.location.lng(), 6);
    Serial.println();

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);  // Start at top-left corner
    display.print(gps.location.lat(), 6);
    display.println();
    display.println();
    display.print(gps.location.lng(), 6);
    display.display();
  } else {
    Serial.println(F("Location not yet valid"));
  }
}

void startupText() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);  // Start at top-left corner
  display.println(F("ESP32 GPS"));
  display.println(F("Sketch"));
  display.display();
  delay(3000);
}
