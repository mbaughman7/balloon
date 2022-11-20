
#include "MSbarometer.h"
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <MS5607.h>

MS5607 P_Sens;

void initialize_barometer() {
  if (!P_Sens.begin()) {
    Serial.println("Error in Communicating with sensor, check your connections!");
  } else {
    Serial.println("MS5607 initialization successful!");
  }
}

float getAltitude(){
  return(P_Sens.getAltitude());
}

