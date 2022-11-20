#include "temperatureSensor.h"

int interior_sensor = A0;
int exterior_sensor = A1;
float interior_temperature;
float exterior_temperature;


void setup() {
  Serial.begin(9600);
  Serial.println("This is the temperature sensor sketch");
  Serial.println("For now, it's just printing random analog values from two different pins.");
  Serial.println("These represent future temp sensors.");
}

void loop() {
  interior_temperature = readTemperature(interior_sensor);
  Serial.print("Interior temperature is: ");
  Serial.println(interior_temperature);
  exterior_temperature = readTemperature(exterior_sensor);
  Serial.print("Exterior temperature is: ");
  Serial.println(exterior_temperature);
  Serial.println("");
  delay(1000);
}
