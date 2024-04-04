#include "textScroller.h"



TextScroller::TextScroller() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {}


bool TextScroller::begin()
{
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
		return false;
	}
	display.setTextSize(1);
	display.setTextColor(SSD1306_WHITE);
	display.clearDisplay();
	display.display();
	display.setTextWrap(false);
	return true;
}


void TextScroller::update()
{
	if (newline) {
		++current_top += fast_scroll;
		if (current_top >= 0x80) {
			current_top = 0x40;
		}
		display.ssd1306_command(current_top);
		display.display();

		if (current_top % 8 == 0) {
			display.setCursor(0, screen_top);
			display.print(next_line);
			display.display();
			newline = false;
		}
	}

	if (buffer.available() > 0 && !newline) {
		char buf[22];
		buffer.getline(buf);
		_write(buf, 21);
		screen_top = current_top - 0x40;
		display.fillRect(0, screen_top, SCREEN_WIDTH, 8, BLACK);
		newline = true;
	}

}


void TextScroller::_write(char* text, size_t textlen) {
	screen_top = current_top - 0x40;
	display.fillRect(0, screen_top, SCREEN_WIDTH, 8, BLACK);
	memcpy(next_line, text, textlen);
	next_line[LINE_LEN] = '\0';
}


void TextScroller::write(char* text, size_t textlen) {
	int lines = textlen / LINE_LEN;
	if (buffer.freeSpace() > lines) {
		for (int i = 0; i <= lines; i ++) {
			buffer.putline(text + i * LINE_LEN);
		}
	}
}


TextBuffer* TextScroller::getBuffer()
{
    return &buffer;
}

