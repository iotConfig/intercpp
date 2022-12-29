#ifndef CPP_INT_TOKENIZER
#define CPP_INT_TOKENIZER

#include "Stream.h"
#include <string>
#include <stdio.h>
using namespace std;

class Tokenizer {
 public:
  Tokenizer(Stream &);
  void setSeparator(char *tab);
  bool isSeparator(char c);
  string nextToken();
 private:
  char *separator;
  Stream &stream;
  char *buff;
  int buffSize;
};

#endif
