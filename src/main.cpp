#include <Arduino.h>
#include "wireless.h"
// #include "barometric.h"
// #include "gps.h"
// #include "data.h"
#include "textScroller.h"


// #define GPS_PIN   2
// #define HC12_RX   9
// #define HC12_TX   8

// #define PUBLISH_FREQ 5000


TextScroller textScroller;
// // GPS gps(GPS_PIN);
Wireless wireless(&textScroller);
// Barometric barometric;



void setup() {
	SerialUSB.begin(9600);

	while(!SerialUSB);

	SerialUSB.println("Start");
  	// init wireless
	// wireless.setSettingsPin(A0);
	// while (!wireless.begin(0)) {
	// 	unsigned long retryMillis = millis();
	// 	while(retryMillis + 1000 > millis()) {}
	// }
	wireless.begin(0);
	// delay(200);
	// init gps
	// gps.begin(9600);
	// barometric.begin();
	SerialUSB.println(textScroller.begin()? "textScroller success" : "textScroller fail");
}

void loop() {
	// SerialUSB.println(ctr++);
  	wireless.update();
	// // barometric.update();
	// // gps.update();
	textScroller.update();


	// if (gps.hasValidData()) {
	// 	char buffer[128];
	// 	gps.readDataIntoBuffer(buffer, BUFFER_SIZE);
	// 	wireless.transmit(buffer, 128);
	// 	// Serial.println(buffer);
	// }
	

	// if (barometric.dataReady()) {
	// 	double pressure;
	// 	double temperature;
	// 	if (barometric.getData(pressure, temperature)){
	// 		wireless.transmit("P=", pressure);
	// 		wireless.transmit("T=", temperature);
	// 		// Serial.print("P: ");
	// 		// Serial.println(pressure);
	// 		// Serial.print("T: ");
	// 		// Serial.println(temperature);
	// 	}
	// }
}
