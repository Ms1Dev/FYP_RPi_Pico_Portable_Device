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


Wireless::Wireless(ScreenMessager* screenMessager) 
{
    this->screenMessager = screenMessager;
}


bool Wireless::begin(int mode)
{
    Serial1.begin(9600);
    return true;
}


void Wireless::update()
{
    if (Serial1.available()) {
        char buffer[128];
        int i = 0;
        do {
            char c = Serial1.read();
            buffer[i++] = c;
            delay(10);
        } while (Serial1.available());
        buffer[i] = '\0';
        // SerialUSB.println(buffer);
        screenMessager->write(buffer, i+1);
        if(strstr(buffer,"␅") != nullptr) {
            char idBuff[5];
            memcpy(idBuff, &buffer[3], 3);
            idBuff[4] = '\0';
            Serial1.print("␆");
            Serial1.println(idBuff);
        }
    }
}