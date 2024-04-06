#include "gps.h"
#include <Arduino.h>


GPS::GPS()
{}


void GPS::begin()
{
    Serial2.setRX(GPS_RX_PIN);
    Serial2.setTX(GPS_TX_PIN);
    Serial2.begin(9600);
}


void GPS::update()
{
    while (Serial2.available()) {
        gps.encode(Serial2.read());
    }
}


bool GPS::dataAvailable()
{
    if (!gps.location.isUpdated() || !gps.location.isValid()) return false;
    return _lng != gps.location.lng() && _lat != gps.location.lat();
}


void GPS::getData(double &lat, double &lng)
{
    _lat = lat = gps.location.lat();
    _lng = lng = gps.location.lng();
}
