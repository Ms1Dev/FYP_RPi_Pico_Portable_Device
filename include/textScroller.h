#ifndef TEXTSCROLLER_H
#define TEXTSCROLLER_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "textBuffer.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 

#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C 

#include "screenMessager.h"

class TextScroller : public ScreenMessager
{
private:
    TextBuffer buffer;
    int current_top = 0x40;
    char next_line[LINE_LEN +1];
    bool newline = false;
    bool fast_scroll = true;
    int screen_top = 0;
    Adafruit_SSD1306 display;
    void _write(char* text, size_t textlen);
public:
    TextScroller();
    bool begin();
    void update();
    void write(char* text, size_t textlen);
    TextBuffer* getBuffer();
};



#endif