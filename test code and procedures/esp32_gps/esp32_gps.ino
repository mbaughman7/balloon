#include <SparkFun_I2C_GPS_Arduino_Library.h>  //Use Library Manager or download here: https://github.com/sparkfun/SparkFun_I2C_GPS_Arduino_Library
#include <TinyGPS++.h>                         //From: https://github.com/mikalhart/TinyGPSPlus
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
I2CGPS myI2CGPS;  
TinyGPSPlus gps;  
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); //set up built-in oled screen on wemos lolin32


void setup() {
  Serial.begin(115200);
  Serial.println("esp32 with screen and gps");
  Wire.begin(5, 4);
  if (myI2CGPS.begin() == false) {
    Serial.println("No GPS module found.");
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

    if (gps.altitude.isValid())
  {
    Serial.print(F("Altitude Meters:"));
    Serial.print(gps.altitude.meters());
    Serial.print(F(" Feet:"));
    Serial.print(gps.altitude.feet());
    display.print(gps.altitude.feet());
    display.print("ft");
    display.display();
  }

  if (gps.satellites.isValid())
  {
    Serial.print(F(" Satellites in View:"));
    Serial.print(gps.satellites.value());
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
