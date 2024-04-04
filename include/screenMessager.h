#ifndef SCREENMESSAGER_H
#define SCREENMESSAGER_H


class ScreenMessager 
{
public:
    virtual void write(char* text, unsigned int textlen) = 0;
};


#endif