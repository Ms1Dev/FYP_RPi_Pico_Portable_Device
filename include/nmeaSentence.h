#ifndef NMEASENTENCE_H
#define NMEASENTENCE_H

struct NmeaSentence{
    const char* id = "$GNGGA,";
    static const char checksumDelimeter = '*';
    static const unsigned char dataBufferSize = 82;
    char data[dataBufferSize];
    int dataLen;
    char checksum[3];
};

#endif