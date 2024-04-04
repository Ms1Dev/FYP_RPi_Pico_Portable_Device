#ifndef WIRELESS_H
#define WIRELESS_H

#include "data.h"
#include "screenMessager.h"


class Wireless 
{
private:
    ScreenMessager* screenMessager;
public:
    Wireless (ScreenMessager* screenMessager);
    void transmit(char *buffer, int buffer_size);
    void transmit(const char *label, double data);
    bool begin(int mode);
    void update();
};

#endif