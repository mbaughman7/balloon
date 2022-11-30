/* According to the graph in the UV sensor documentation, the sensor should have a photocurrent of 1uA
  at 9 mW/square cm of UV-A radiation and 1.5uA at 13.5 mW/square cm.   
  Pretty sure if you revisit the ol' y = mx + b, you should be able to
  estimate UV power.  But the signal spit out by the UV sensor is just arbitrary analog girth units?  Not microamps?
  I dunno.  Testing required. 
*/

#include "uvSensor.h"
#include <Arduino.h>

int readUV(int sensorPin) {
  int uv_girth_units;

  uv_girth_units = analogRead(sensorPin);
  return uv_girth_units;
}