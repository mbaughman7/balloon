#include "gps.h"
#include "sdCard.h"
#include <MemoryFree.h>
#include <Servo.h>

Servo pinPullingServo;

double gps_altitude;
double lat;
double longitude;
double sats;
double speed;

int inital_altitude;
int TARGET_HEIGHT = 75;

unsigned long previousMillis = 0;  // Stores the last time the loop was executed
const long interval = 15000;       // Interval at which to take readings (milliseconds)

void setup() {
  Serial.begin(9600);
  Serial.println("This is a test based on altitude.  A payload is dropped at a predetermined height.");
  Initialize_SDcard();
  initialize_gps();
  update_gps();
  inital_altitude = get_altitude();
  pinPullingServo.attach(9);
  pinPullingServo.write(0);
}

void loop() {
  unsigned long currentMillis = millis();  // Get the current time

  update_gps();
  speed = get_speed();
  gps_altitude = get_altitude();
  lat = get_lat();
  longitude = get_long();
  sats = get_sats();

  // Check if it's time to take readings
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Save the current time

    Serial.println("Now saving to SD card...");
    Serial.print("altitude: ");
    Serial.println(gps_altitude);
    write_to_SD(lat, longitude, sats, speed, gps_altitude);
    Serial.print(freeMemory());
    Serial.println("");
  }

  // If Boba has reached a height at or above the target height with respect to the starting altitude, the servo actuates.
  if (gps_altitude - inital_altitude >= TARGET_HEIGHT){
    Serial.println("actuating servo and releasing payload");
    pinPullingServo.write(90);
    Serial.println("Now saving to SD card...");
    Serial.print("altitude: ");
    Serial.println(gps_altitude);
    write_to_SD(lat, longitude, sats, speed, gps_altitude);
    Serial.print(freeMemory());
    Serial.println("");    
  }
}
