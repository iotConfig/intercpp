#ifndef _INTER_CPP_CHAR_STREAM
#define  _INTER_CPP_CHAR_STREAM
#include "Stream.h"

class CharStream : public Stream
{
 public:
  CharStream(const char *);
  char next();
 private:
  const char *buff;
  int i;
};

#endif
