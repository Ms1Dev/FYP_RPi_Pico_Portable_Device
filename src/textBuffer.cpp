// #include "textBuffer.h"



// int TextBuffer::putline(char* item) 
// {
//    if ((head + 1) % size == tail)
//    {
//       return 0;
//    }

//    memcpy(lines[head], item, LINE_LEN);

//    head = (head + 1) % size;
//    return 1;
// }


// int TextBuffer::getline(char * value) 
// {
//   if (tail == head)
//   {
//      return 0;
//   }

//   memcpy(value, lines[tail], LINE_LEN);

//   tail = (tail + 1) % size;
//   return 1;
// }


// bool TextBuffer::available()
// {
//     return tail != head;
// }


// int TextBuffer::freeSpace()
// {
//    if (head >= tail) {
//       return size - (head - tail) - 1;
//    } else {
//       return head - head - 1;
//    }
// }

