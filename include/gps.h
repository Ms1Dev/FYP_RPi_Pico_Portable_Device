#ifndef GPS_H
#define GPS_H

#include <TinyGPS++.h>
#include "nmeaSentence.h"

class GPS
{
private:
    bool hasNewData = false;
    TinyGPSPlus gps;
    double lat,lng;
public:
    GPS();
    void begin();
    void update();
    bool dataAvailable();
    void readDataIntoBuffer(char* buffer, int bufferSize);
};

#endif