#ifndef TEXTBUFFER_H
#define TEXTBUFFER_H

#include <Arduino.h>

#define LINE_LEN 21
#define ROW_COUNT 8

class TextBuffer
{
    uint8_t head = 0;
    uint8_t tail = 0;
    static const size_t size = ROW_COUNT;
    char lines[size][LINE_LEN];
    size_t len = 0;
public:
    int getline(char* buff);
    int putline(char* line);
    bool available();
    int freeSpace();
};

#endif