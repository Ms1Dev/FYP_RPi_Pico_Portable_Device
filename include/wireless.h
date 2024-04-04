#ifndef WIRELESS_H
#define WIRELESS_H

#include "data.h"
#include "screenMessager.h"

#define SERIAL_IN_BUFFER 512

#define READ_TIMOUT_MS 20

class Wireless 
{
private:
    ScreenMessager* screenMessager;
    char buffer[SERIAL_IN_BUFFER];
    int i = 0;
    void _processBuffer();
    unsigned long read_timout_millis = 0;
public:
    Wireless (ScreenMessager* screenMessager);
    void transmit(char *buffer, int buffer_size);
    void transmit(const char *label, double data);
    bool begin(int mode);
    void update();
};

#endif