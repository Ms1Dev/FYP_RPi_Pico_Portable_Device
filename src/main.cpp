#include <Arduino.h>
#include "wireless.h"
#include "textScroller.h"
#include "textBuffer.h"
#include "gps.h"


#define TX_BUFF_ROWS 8
#define TX_BUFF_COLS 128


TextScroller textScroller;
Wireless wireless(&textScroller);
GPS gps;


volatile int ctr = 0;

TextBuffer<TX_BUFF_ROWS, TX_BUFF_COLS> transmitBuffer;


void setup() 
{
	Serial.begin(9600);
	while(!Serial);
	Serial.println("Start");
	wireless.begin(0);
}

void loop() 
{
	wireless.update();

	if (transmitBuffer.available()) {
		char b[128];
		transmitBuffer.getline(b);
		Serial.println(b);
	}
}


void setup1() 
{
	// textScroller.begin();
	gps.begin();
}


void loop1()
{
	// textScroller.update();
	gps.update();

	if (gps.dataAvailable()) {
		char buffer[128];
		gps.readDataIntoBuffer(buffer, BUFFER_SIZE);
		transmitBuffer.putline(buffer);
	}
}