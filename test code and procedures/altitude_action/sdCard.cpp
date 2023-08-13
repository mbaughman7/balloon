#include <SD.h>
#include <MemoryFree.h>


void Initialize_SDcard() {
  // see if the card is present and can be initialized:
  if (!SD.begin(10)) {
    Serial.println("Card failed or not present");
    return;
  }

  File dataFile = SD.open("ALT1.txt", FILE_WRITE);

  if (dataFile) {
    dataFile.println("latitude,longitude,satellites,speed,gps_altitude");  //Write the first row of the csv
    dataFile.close();
    Serial.println("successfully opened and primed SD card file");
  } else {
    Serial.println("couldn't open file");
  }
}

void write_to_SD(double lat, double longitude, double sats, double speed, double gps_altitude) {

  File dataFile = SD.open("ALT1.txt", FILE_WRITE);


  if (dataFile) {


    dataFile.print(String(lat,6));
    dataFile.print(",");

    dataFile.print(String(longitude,6));
    dataFile.print(",");


    dataFile.print(sats);
    dataFile.print(",");

    dataFile.print(speed);
    dataFile.print(",");

    dataFile.print(gps_altitude);
    dataFile.print(",");

    dataFile.println();  //End of Row move to next row
    dataFile.close();    //Close the file
    Serial.print(freeMemory());
  } else
    Serial.println("SD card writing failed");
}