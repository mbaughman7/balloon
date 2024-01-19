#include "temperatureSensor.h"
#include "MSbarometer.h"
#include "uvSensor.h"
#include "gps.h"
#include "sdCard.h"
#include "accTemp.h"
#include <MemoryFree.h>

int interior_sensor = A0;
int exterior_sensor = A1;
int uv_sensor = A2;
float interior_temperature;
float exterior_temperature;
float accTempF;
double gps_altitude;
double lat;
double longitude;
double sats;
double speed;
// float altitude;
int uv_value;

unsigned long previousMillis = 0;  // Stores the last time the loop was executed
const long interval = 1000;       // shorter interval than the main balloon code

void setup() {
  Serial.begin(9600);
  Serial.println("This is balloon code displaying GPS and UV sensor data to the serial monitor. All values are also saved to variables to be saved to the SD card for logging in the future.");
  initialize_barometer();  // this barometer is the MS5607 high altitude, high precision barometer. As of this version, we ain't got one yet. This is just here for the future.
  Initialize_SDcard();
  initialize_accTemp();
  initialize_gps();
}

void loop() {
  unsigned long currentMillis = millis();  // Get the current time

  update_gps();
  speed = get_speed();
  gps_altitude = get_altitude();
  lat = get_lat();
  longitude = get_long();
  sats = get_sats();
  uv_value = readUV(uv_sensor);
  accTempF = getAccTemp();

  // Check if it's time to take readings
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Save the current time

    Serial.println("Now saving to SD card...");
    Serial.print("lat: ");
    Serial.println(lat,6);
    Serial.print("long: ");
    Serial.println(longitude,6);
    Serial.print("altitude: ");
    Serial.println(gps_altitude);
    Serial.print("Super duper accurate temperature in F: ");
    Serial.println(accTempF);
    write_to_SD(lat, longitude, sats, speed, gps_altitude, uv_value, accTempF);
    Serial.print(freeMemory());
    Serial.println("");
    Serial.println("");
  }
}
