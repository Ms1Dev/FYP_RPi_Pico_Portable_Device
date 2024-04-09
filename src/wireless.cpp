#include "wireless.h"
#include <Arduino.h>

void Wireless::transmit(char *buffer, int buffer_size)
{
    for (int i = 0; i < buffer_size; i++) {
        Serial1.print(buffer[i]);
        if (buffer[i] == '\0') break;
    }
    Serial1.println();
}


void Wireless::transmit(const char *label, double data)
{
    Serial1.print(label);
    Serial1.println(data);
}


Wireless::Wireless(ScreenMessager *screenMessager)
{
    this->screenMessager = screenMessager;
}


bool Wireless::begin(int mode)
{
    Serial1.begin(9600);
    return true;
}

void Wireless::_processBuffer()
{
    screenMessager->putText(buffer, i+1);
    if(strstr(buffer,"␅") != nullptr) {
        char idBuff[5];
        memcpy(idBuff, &buffer[3], 3);
        idBuff[4] = '\0';
        Serial1.print("␆");
        Serial1.println(idBuff);
    }
    i = 0;
}


void Wireless::update()
{
    unsigned long current_millis = millis();

    if (Serial1.available()) {
        read_timout_millis = current_millis;

        char c = Serial1.read();
        buffer[i++] = c;

        if (c == '\n' || c == '\0' ||  c == '\r' || i >= SERIAL_IN_BUFFER) {
            buffer[i] = '\0';
            _processBuffer();
        }
    }
    else if (current_millis > read_timout_millis + READ_TIMOUT_MS && i > 0) {
        read_timout_millis = current_millis;
        buffer[i] = '\0';
        _processBuffer();
    }
}