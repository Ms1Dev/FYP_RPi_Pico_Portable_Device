#include <Arduino.h>
#include "wireless.h"
#include "textScroller.h"
#include <pico.h>
#include <cppQueue.h>


TextScroller textScroller;
Wireless wireless(&textScroller);

volatile int ctr = 0;

// cppQueue recvQueue(sizeof(char), 1024, FIFO);

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
}


void setup1() 
{
	textScroller.begin();
}


void loop1()
{
	textScroller.update();
}