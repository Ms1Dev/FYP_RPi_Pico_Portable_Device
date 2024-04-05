#ifndef TEXTBUFFER_H
#define TEXTBUFFER_H

#include <Arduino.h>


template<int _Size, int _LineLen>
class TextBuffer
{
    uint8_t head = 0;
    uint8_t tail = 0;
    char lines[_Size][_LineLen];
    size_t len = 0;
public:
    int getline(char* buff);
    int putline(char* line);
    bool available();
    int freespace();
};


template<int _Size, int _LineLen>
int TextBuffer<_Size,_LineLen>::putline(char* item) 
{
   if ((head + 1) % _Size == tail)
   {
      return 0;
   }

   memcpy(lines[head], item, _LineLen);

   head = (head + 1) % _Size;
   return 1;
}


template<int _Size, int _LineLen>
int TextBuffer<_Size,_LineLen>::getline(char * value) 
{
  if (tail == head)
  {
     return 0;
  }

  memcpy(value, lines[tail], _LineLen);

  tail = (tail + 1) % _Size;
  return 1;
}


template<int _Size, int _LineLen>
bool TextBuffer<_Size,_LineLen>::available()
{
    return tail != head;
}


template<int _Size, int _LineLen>
int TextBuffer<_Size,_LineLen>::freespace()
{
   if (head >= tail) {
      return _Size - (head - tail) - 1;
   } else {
      return head - head - 1;
   }
}


#endif