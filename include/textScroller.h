#ifndef TEXTSCROLLER_H
#define TEXTSCROLLER_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "textBuffer.h"
#include "screenMessager.h"


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 
#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C 


class TextScroller : public ScreenMessager
{
private:
    static const int buffer_rows = 64;
    static const int line_len = 21;

    TextBuffer<buffer_rows, line_len> buffer;
    Adafruit_SSD1306 display;

    int current_top = 0x40;
    char next_line[line_len +1];
    bool writing = false;
    bool fast_scroll = true;
    int screen_top = 0;
    
    void _write(char* text, size_t textlen);

public:
    TextScroller();
    bool begin();
    void update();
    void putText(char* text, size_t textlen);
};



#endif