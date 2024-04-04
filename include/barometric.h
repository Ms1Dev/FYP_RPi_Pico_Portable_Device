#ifndef BAROMETRIC_H
#define BAROMETRIC_H

#include <MS5611.h>
#include <Wire.h>

class Barometric
{
private:
    enum State {
        REQUEST_TEMP,
        RECEIVE_TEMP,
        REQUEST_PRES,
        RECEIVE_PRES
    };
    State state = State::REQUEST_TEMP;
    unsigned long state_change_millis = 0;
    char wait_millis = 0;

    const int min_samples_per_result = 1;
    bool in_error = false;

    MS5611 pressure;

    double press_total = 0;
	double temp_total = 0;
    double press_reading = 0;
    double temp_reading = 0;
    double press = 0;
    double temp = 0;
    int read_count = 0;
    bool data_ready = false;
public:
    Barometric();
    void begin();
    void update();
    bool dataReady();
    bool getData(double &pressure, double &temperature);
};

#endif