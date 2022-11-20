#include "temperatureSensor.h"
#include <Arduino.h>

float readTemperature(int sensorPin) {
  float temperature;

  temperature = analogRead(sensorPin);
  return temperature;
}