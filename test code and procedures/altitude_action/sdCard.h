#ifndef SDCARD_H
#define SDCARD_H

void Initialize_SDcard();
void write_to_SD(double lat,double longitude, double sats, double speed, double gps_altitude);

#endif