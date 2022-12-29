#include "CharStream.h"
#include <string>

CharStream::CharStream(const char *exp):
  buff(exp), i(0)
{  
}

char CharStream::next()
{
  if (i <= strlen(buff))
    return buff[i++];
  else 
    return 0;
}
