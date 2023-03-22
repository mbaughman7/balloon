#include "temperatureSensor.h"
#include "MSbarometer.h"
#include "uvSensor.h"
#include "gps.h"

int interior_sensor = A0;
int exterior_sensor = A1;
int uv_sensor = A2;
float interior_temperature;
float exterior_temperature;
float altitude;
int uv_value;

void setup() {
  Serial.begin(9600);
  Serial.println("This is balloon code with interior/exterior temps and barometer.");
  Serial.println("The barometer has not been tested yet, and the temp sensors are just simulated until combined with known-value resistor");
  initialize_barometer();
  initialize_gps();
}

void loop() {

  altitude = getAltitude();
  Serial.print("Altitude is: ");
  Serial.println(altitude);
  uv_value = readUV(uv_sensor);
  Serial.print("UV value is: ");
  Serial.println(uv_value);
  Serial.println("");
  display_gps();
  Serial.println("");
  delay(1000);

  /*when ready, the main loop can get rid of serial prints and 
   * consist of simply setting all of the data points and then
   * saving those to the SD card.
   * 
   *   interior_temperature = readTemperature(interior_sensor);
   *   exterior_temperature = readTemperature(exterior_sensor);
   *   altitude = getAltitude();
   *   uv_value = readUV(uv_sensor);
   *   SaveAllThisStuffToSD();
   */

}
