#ifndef GPS_H
#define GPS_H

#include <TinyGPS++.h>
#include "nmeaSentence.h"

#define GPS_RX_PIN 9
#define GPS_TX_PIN 8


class GPS
{
private:
    TinyGPSPlus gps;
    double _lat,_lng;
public:
    GPS();
    void begin();
    void update();
    bool dataAvailable();
    void getData(double &lat, double &lng);
};

#endif