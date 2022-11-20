#include "temperatureSensor.h"
#include "MSbarometer.h"

int interior_sensor = A0;
int exterior_sensor = A1;
float interior_temperature;
float exterior_temperature;
float altitude;

void setup() {
  Serial.begin(9600);
  Serial.println("This is balloon code with interior/exterior temps and barometer.");
  Serial.println("The barometer has not been tested yet, and the temp sensors are just simulated until combined with known-value resistor");
  initialize_barometer();
}

void loop() {
  interior_temperature = readTemperature(interior_sensor);
  Serial.print("Interior temperature is: ");
  Serial.println(interior_temperature);
  exterior_temperature = readTemperature(exterior_sensor);
  Serial.print("Exterior temperature is: ");
  Serial.println(exterior_temperature);
  altitude = getAltitude();
  Serial.print("Altitude is: ");
  Serial.println(altitude);
  Serial.println("");
  delay(1000);

  /*when ready, the main loop can get rid of serial prints and 
   * consist of simply setting all of the data points and then
   * saving those to the SD card.
   * 
   *   interior_temperature = readTemperature(interior_sensor);
   *   exterior_temperature = readTemperature(exterior_sensor);
   *   altitude = getAltitude();
   *   SaveAllThisStuffToSD();
   */

}
