## Pico Powered Position Transmitter

Device that transmits its current position using a GNSS receiver and a barometric pressure sensor. It also has an OLED so it could demonstrate 2-way communication.
The Pico was programmed on PlatformIO using Earl Philhowers <a href="https://arduino-pico.readthedocs.io/en/latest/index.html">Arduino-Pico</a> core. 
This was part of my final year project for developing a tracking antenna and this device was used as the target for the antenna to track.

To control the OLED I've used the <a href="https://github.com/adafruit/Adafruit_SSD1306">Adafruit SSD1306</a> library. It doesn't directly allow vertically scrolling text so I had to get a bit inventive to make it work.
Parsing the GNSS data was possible thanks to the <a href="https://github.com/mikalhart/TinyGPSPlus">TinyGPSPlus</a> library and worked superbly I would highly recommend it for any GPS Arduino projects. 


<img src="https://github.com/Ms1Dev/FYP_RPi_Pico_Portable_Device/blob/main/PXL_20240415_162539884.jpg" alt="Photo of device" height="500"/>
