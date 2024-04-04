#ifndef GPS_H
#define GPS_H

#include "nmeaSentence.h"

class GPS
{
private:
    NmeaSentence sentence;
    bool hasNewData = false;
    bool isValidData = false;
    bool hasFix = false;
    bool receivingResponse = true;
    const int waitForResponse = 10000;
    unsigned long lastReceive = 0;
    unsigned char initialChecksumVal;
    unsigned long sampleMillis = 0;
    int sampleFrequency = 2000;
    unsigned char _parseChecksum(char* checksum);
    unsigned char _calcChecksum(NmeaSentence *sentence);
    bool _validateData(NmeaSentence *sentence);
    bool _checkDataForFix(NmeaSentence *sentence);
public:
    GPS(int pwrPin);
    void begin(int baudrate);
    void update();
    char *getData();
    NmeaSentence *getSentence();
    bool ready();
    bool dataAvailable();
    bool dataIsValid();
    bool hasPositionFix();
    bool hasValidData();
    bool isCommunicating();
    void updateState();
    void readDataIntoBuffer(char* buffer, int bufferSize);
    void setSampleFrequency(int freq);
};

#endif