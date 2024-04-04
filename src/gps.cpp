#include "gps.h"
#include <Arduino.h>


unsigned char GPS::_parseChecksum(char *checksum)
{
    unsigned char parsedChecksum = strtol(checksum, 0, 16);
    return parsedChecksum;
}


unsigned char GPS::_calcChecksum(NmeaSentence *sentence)
{
    unsigned char checkVal = initialChecksumVal;

    for (int i = 0; i < sentence->dataLen; i++) {
        char data = sentence->data[i];
        checkVal ^= data;
    }

    return checkVal;
}


bool GPS::_validateData(NmeaSentence *sentence)
{
    unsigned char checksum = _parseChecksum(sentence->checksum);
    unsigned char calculatedChecksum = _calcChecksum(sentence);
    return checksum == calculatedChecksum;
}


bool GPS::_checkDataForFix(NmeaSentence *sentence)
{
    int commaPos = 0;
    int commaCount = 0;
    for (int i = 0; i < sentence->dataLen; i++) {
        if (sentence->data[i] == ',') {
            if (i - commaPos == 1) {
                return false;
            }
            commaPos = i;
            commaCount++;
            if (commaCount > 5) break;
        }
    }
    return true;
}


GPS::GPS(int pwrPin)
{
    pinMode(pwrPin, OUTPUT);
    digitalWrite(pwrPin, HIGH);
    initialChecksumVal = 0;
    for (int i = 1; i < 7; i++) {
        initialChecksumVal ^= sentence.id[i];
    }
}


void GPS::begin(int baudrate)
{
    Serial.begin(baudrate);
}


void GPS::update()
{
    unsigned long currentMillis = millis();

    if (currentMillis > lastReceive + waitForResponse) {
        return;
    }
    if (Serial.available()) {
        lastReceive = currentMillis;
        receivingResponse = true;
        // if (currentMillis < sampleMillis + sampleFrequency) return state;
        sampleMillis = currentMillis;
        if(Serial.find((char*) sentence.id)) {
            sentence.dataLen = Serial.readBytesUntil(sentence.checksumDelimeter, sentence.data, sentence.dataBufferSize);
            Serial.readBytesUntil('\n', sentence.checksum, 2);
            sentence.checksum[3] = '\0';
            // isValidData = _validateData(&sentence);
            // hasFix = _checkDataForFix(&sentence);
            isValidData = true;
            hasFix = true;
            hasNewData = true;
        }
    }
}


bool GPS::dataAvailable()
{
    return hasNewData;
}

bool GPS::hasValidData()
{
    return hasFix && isValidData && hasNewData;
}

void GPS::readDataIntoBuffer(char *buffer, int bufferSize)
{
    int idLen = strlen(sentence.id);
    for (int i = 0; i < idLen; i++) {
        buffer[i] = sentence.id[i];
    }
    int j;
    for (j = 0; j < sentence.dataLen; j++) {
        if (j+idLen+4 >= bufferSize) break;
        buffer[j+idLen] = sentence.data[j];
    }
    j += idLen;
    buffer[j++] = '*';
    buffer[j++] = sentence.checksum[0];
    buffer[j++] = sentence.checksum[1];
    buffer[j++] = '\0';
    hasNewData = false;
}

void GPS::setSampleFrequency(int freq)
{
    sampleFrequency = freq;
}
