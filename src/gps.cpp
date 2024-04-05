#include "gps.h"
#include <Arduino.h>


GPS::GPS()
{}


void GPS::begin()
{
    Serial2.setRX(9);
    Serial2.setTX(8);
    Serial2.begin(9600);
}


void GPS::update()
{
    if (Serial2.available()) {
        gps.encode(Serial2.read());
    }
}


bool GPS::dataAvailable()
{
    if (!gps.location.isUpdated() || !gps.location.isValid()) return false;
    return lng != gps.location.lng() && lat != gps.location.lat();
}


void GPS::readDataIntoBuffer(char *buffer, int bufferSize)
{
    lat = gps.location.lat();
    lng = gps.location.lng();
    sprintf(buffer, "G%f,%f", lat, lng);
}
