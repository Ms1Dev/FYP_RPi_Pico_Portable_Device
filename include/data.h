
#ifndef DATA_H
#define DATA_H

#define BUFFER_SIZE 128

namespace data
{
    struct Buffer {
        char payload[BUFFER_SIZE];
        bool toTransmit = false;
    };
    
} // namespace data



#endif