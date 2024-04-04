#include "barometric.h"
#include <Wire.h>


Barometric::Barometric(/* args */) : pressure(0x77)
{}

void Barometric::begin()
{
    pressure.setOversampling(OSR_ULTRA_HIGH);
    pressure.begin();
}

bool Barometric::dataReady()
{
    return data_ready;
}

bool Barometric::getData(double &press, double &temp)
{
    press = press_reading;
    temp = temp_reading;
    data_ready = false;
    return !in_error;
}

void Barometric::update()
{
    pressure.read();
    temp_reading = pressure.getTemperature();
    press_reading = pressure.getPressure();
    data_ready = true;
    
    // unsigned long current_millis = millis();
    

    // if (state == REQUEST_TEMP) {
    //     wait_millis = pressure.startTemperature();
    //     if (wait_millis != 0) {
    //         in_error = false;
    //         state = RECEIVE_TEMP;
    //         state_change_millis = current_millis;
    //     }
    // }

    // if (state == RECEIVE_TEMP && current_millis > state_change_millis + wait_millis) {

    //     if (pressure.getTemperature(temp) != 0) {
    //         in_error = false;
    //         state = REQUEST_PRES;
    //     }
    //     else {
    //         state = REQUEST_TEMP;
    //     }
    // }

    // if (state == REQUEST_PRES) {

    //     wait_millis = pressure.startPressure(3);

    //     if (wait_millis != 0) {
    //         in_error = false;
    //         state = RECEIVE_PRES;
    //         state_change_millis = current_millis;
    //     }
    // }

    // if (state == RECEIVE_PRES && current_millis > state_change_millis + wait_millis) {

    //     if (pressure.getPressure(press,temp) != 0) {
    //         in_error = false;
    //         read_count++;
    //         press_total += press;
    //         temp_total += temp;
    //     }
    //     state = REQUEST_TEMP;
    // }

    // if (read_count >= min_samples_per_result) {
    //     press_reading = press_total / read_count;
    //     temp_reading = temp_total / read_count;
    //     temp_total = 0;
    //     press_total = 0;
    //     read_count = 0;
    //     data_ready = true;
    // }
}
