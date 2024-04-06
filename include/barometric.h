#ifndef BAROMETRIC_H
#define BAROMETRIC_H

#include <MS5611.h>
#include <Wire.h>

class Barometric
{
private:
    const int read_delay_ms = 1000;

    MS5611 ms5611;

    unsigned long last_read_millis = 0;
    double press_total = 0;
	double temp_total = 0;
    int read_count = 0;
    bool data_ready = false;
    bool in_error = false;
public:
    Barometric();
    void begin();
    void update();
    bool dataReady();
    void getData(double &pressure, double &temperature);
};

#endif