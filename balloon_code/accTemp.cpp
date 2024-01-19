#include "accTemp.h"
#include <Wire.h>
#include "Adafruit_MCP9808.h"


Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();


void initialize_accTemp() {
  if (!tempsensor.begin(0x18)) {
    Serial.println("Couldn't find MCP9808! Check your connections and verify the address is correct.");
    while (1)
      ;
  }

  Serial.println("Found MCP9808!");
  tempsensor.wake(); 
  delay(50);
  Serial.println("sensor is awake");
  tempsensor.setResolution(0);  // sets the resolution mode of reading, the modes are defined in the table bellow:
  // Mode Resolution SampleTime
  //  0    0.5°C       30 ms
  //  1    0.25°C      65 ms
  //  2    0.125°C     130 ms
  //  3    0.0625°C    250 ms
}

float getAccTemp(){
  // float c = tempsensor.readTempC();
  float f = tempsensor.readTempF();
  // Serial.print("Temp: ");
  // Serial.print(c, 4);
  // Serial.print("*C\t and ");
  // Serial.print(f, 4);
  // Serial.println("*F.");
  delay(10);
  return(f);
}
