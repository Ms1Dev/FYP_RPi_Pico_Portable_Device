#include "barometric.h"

#include <Arduino.h>


Barometric::Barometric() : ms5611(MS5611_DEFAULT_ADDRESS)
{}


void Barometric::begin()
{    
    Wire.begin();
    ms5611.setOversampling(OSR_ULTRA_HIGH);
    ms5611.begin();
}


bool Barometric::dataReady()
{
    return data_ready && !in_error;
}


void Barometric::getData(double &press, double &temp)
{
    press = press_total / read_count;
    temp = temp_total / read_count; 
    data_ready = temp_total = press_total = read_count = 0;
}


void Barometric::update()
{
    in_error = ms5611.read() != MS5611_READ_OK;
    if (!in_error) {
        temp_total += ms5611.getTemperature();
        press_total += ms5611.getPressure();
        read_count++;
    }

    unsigned long current_millis = millis();
    if (current_millis >= last_read_millis + read_delay_ms) {
        last_read_millis = current_millis;
        data_ready = true;
    }
}
