#include <Arduino.h>
#include "wireless.h"
#include "textScroller.h"
#include "textBuffer.h"
#include "gps.h"
#include "barometric.h"

#define TX_BUFF_ROWS 8
#define TX_LINE_LEN 48


TextScroller textScroller;
Wireless wireless(&textScroller);
GPS gps;
Barometric barometric;

TextBuffer<TX_BUFF_ROWS, TX_LINE_LEN> transmitBuffer;


void setup() 
{
	Serial.begin(9600);
	while(!Serial);
	wireless.begin(0);
}


void loop() 
{
	wireless.update();

	if (transmitBuffer.available()) {
		char buffer[TX_LINE_LEN];
		transmitBuffer.getline(buffer);
		wireless.transmit(buffer, TX_LINE_LEN);
		// Serial.println(buffer);
	}
}


void setup1() 
{
	barometric.begin();
	textScroller.begin();
	gps.begin();
}


void loop1()
{
	barometric.update();
	textScroller.update();
	gps.update();
	
	if (barometric.dataReady()) {
		char buffer[TX_LINE_LEN];
		double press,temp;
		barometric.getData(press,temp);
		sprintf(buffer, "P=%f\nT=%f", press, temp);
		transmitBuffer.putline(buffer);
	}

	if (gps.dataAvailable()) {
		char buffer[TX_LINE_LEN];
		double lat,lng;
		gps.getData(lat,lng);
		sprintf(buffer, "G=%f,%f", lat, lng);
		transmitBuffer.putline(buffer);
	}
}