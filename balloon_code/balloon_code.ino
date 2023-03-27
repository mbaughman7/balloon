#include "temperatureSensor.h"
#include "MSbarometer.h"
#include "uvSensor.h"
#include "gps.h"
#include "sdCard.h"

int interior_sensor = A0;
int exterior_sensor = A1;
int uv_sensor = A2;
float interior_temperature;
float exterior_temperature;
double gps_altitude;
double lat;
double longitude;
double sats;
double speed;
// float altitude;
int uv_value;

void setup() {
  Serial.begin(9600);
  Serial.println("This is balloon code displaying GPS and UV sensor data to the serial monitor.  All values are also saved to variables to be saved to the SD card for logging in the future.");
  initialize_barometer();  //this barometer is the MS5607 high altitude, high precision barometer.  As of this version, we ain't got one yet. This just here for the future.
  Initialize_SDcard();

  initialize_gps();
}

void loop() {
  update_gps();
  speed = get_speed();
  gps_altitude = get_altitude();
  lat = get_lat();
  longitude = get_long();
  sats = get_sats();
  uv_value = readUV(uv_sensor);
  Serial.print("UV value is: ");
  Serial.println(uv_value);
  Serial.println("Now saving to SD card...");
  write_to_SD(lat,longitude,sats,speed,gps_altitude,uv_value);

  // display_gps();
  Serial.println("");
  delay(15000);
}
