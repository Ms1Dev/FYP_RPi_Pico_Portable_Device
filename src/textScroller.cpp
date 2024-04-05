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
	if (writing) {
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
			writing = false;
		}
	}

	if (buffer.available() > 0 && !writing) {
		char buf[line_len +1];
		buffer.getline(buf);
		_write(buf, line_len);
		screen_top = current_top - 0x40;
		display.fillRect(0, screen_top, SCREEN_WIDTH, 8, BLACK);
		writing = true;
	}

}


void TextScroller::_write(char* text, size_t textlen) {
	screen_top = current_top - 0x40;
	display.fillRect(0, screen_top, SCREEN_WIDTH, 8, BLACK);
	memcpy(next_line, text, textlen);
	next_line[line_len] = '\0';
}


void TextScroller::putText(char* text, size_t textlen) {
	int lines = textlen / line_len;
	if (buffer.freespace() > lines) {
		for (int i = 0; i <= lines; i ++) {
			buffer.putline(text + i * line_len);
		}
	}
}

