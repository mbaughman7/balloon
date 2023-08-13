#include <SparkFun_I2C_GPS_Arduino_Library.h>
#include <TinyGPS++.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

I2CGPS myI2CGPS;
TinyGPSPlus gps;



void initialize_gps() {
  Serial.println("Initializing GPS module...");
  Wire.begin();
  if (myI2CGPS.begin() == false) {
    Serial.println("NO GPS MODULE FOUND.");  //consider adding automatic rebooting functionality here? Need some response.
  }
  Serial.println("GPS module found.  Please allow time for satellite acquisition.");
}


void display_gps() {
  //We have new GPS data to deal with!
  Serial.println();
  while (myI2CGPS.available())  //available() returns the number of new bytes available from the GPS module
  {
    gps.encode(myI2CGPS.read());  //Feed the GPS parser
  }

  if (gps.time.isUpdated())  //Check to see if new GPS info is available
  {

    if (gps.time.isValid()) {
      // Serial.print(F("Date: "));
      // Serial.print(gps.date.month());
      // Serial.print(F("/"));
      // Serial.print(gps.date.day());
      // Serial.print(F("/"));
      // Serial.print(gps.date.year());

      // Serial.print((" Time: "));
      // if (gps.time.hour() < 10) Serial.print(F("0"));
      // Serial.print(gps.time.hour());
      // Serial.print(F(":"));
      // if (gps.time.minute() < 10) Serial.print(F("0"));
      // Serial.print(gps.time.minute());
      // Serial.print(F(":"));
      // if (gps.time.second() < 10) Serial.print(F("0"));
      // Serial.print(gps.time.second());

      // Serial.println();  //Done printing time
    } else {
      Serial.println(F("Time not yet valid"));
    }

    if (gps.location.isValid()) {
      // Serial.print("Location: ");
      // Serial.print(gps.location.lat(), 6);
      // Serial.print(F(", "));
      // Serial.print(gps.location.lng(), 6);
      // Serial.println();
    } else {
      Serial.println(F("Location not yet valid"));
    }

    if (gps.altitude.isValid()) {
      // Serial.print(F("Altitude Meters:"));
      // Serial.print(gps.altitude.meters());
      // Serial.print(F(" Feet:"));
      // Serial.print(gps.altitude.feet());
    }

    if (gps.satellites.isValid()) {
      // Serial.print(F(" Satellites in View:"));
      // Serial.println(gps.satellites.value());
    }

    if (gps.speed.isValid()) {
      // Serial.print("Speed: ");
      // Serial.println(gps.speed.mph());
    }
  }
}



void update_gps() {
  while (myI2CGPS.available())  //available() returns the number of new bytes available from the GPS module
  {
    gps.encode(myI2CGPS.read());  //Feed the GPS parser
  }
}

double get_lat() {
  if (gps.location.isValid()) {
    // Serial.print("Lat: ");
    // Serial.print(gps.location.lat(), 6);
    // Serial.println();
    return gps.location.lat();
  } else {
    Serial.println(F("Location not yet valid"));
    return 0;
  }
}

double get_long() {
  if (gps.location.isValid()) {
    // Serial.print("Long: ");
    // Serial.print(gps.location.lng(), 6);
    // Serial.println();
    return gps.location.lng();
  } else {
    Serial.println(F("Location not yet valid"));
    return 0;
  }
}


double get_speed() {
  if (gps.time.isUpdated()) {
    if (gps.speed.isValid()) {
      // Serial.print("Speed: ");
      // Serial.println(gps.speed.mph());
      return (gps.speed.mph());
    } else {
      return 0;
    }
  }
}

double get_sats() {
  if (gps.time.isUpdated()) {
    if (gps.satellites.isValid()) {
      // Serial.print(F("Satellites in View: "));
      // Serial.println(gps.satellites.value());
      return gps.satellites.value();
    } else {
      return 0;
    }
  }
}



double get_altitude() {
  if (gps.time.isUpdated()) {
    if (gps.altitude.isValid()) {
      // Serial.print(F("Altitude Meters:"));
      // Serial.print(gps.altitude.meters());
      // Serial.print(F("Feet: "));
      // Serial.print(gps.altitude.feet());
      // Serial.println();  //Done printing altitude
      return (gps.altitude.feet());
    } else {
      Serial.println(F("Altitude not yet valid"));
      return (0);
    }
  }
}
