#ifndef CPP_INT_FILE
#define CPP_INT_FILE

#include <string>
#include <stdio.h>
#include "Stream.h"
#include "types.h"
#include "Exception.h"

using namespace std;
class File : public Stream{
  
 public:
  File(char *fileName, char *mod, bool bin = false);// throw(exception);
  virtual ~File();
  virtual size_t read(buffer_t buff, size_t size);// throw(NullPointerException);
  virtual bool setFip(fip_t fip);
  virtual fip_t getFip();
  virtual bool write(buffer_t buff, size_t size);
  virtual char next();
  virtual char *readLine();
 private:
  string fileName;
  string mode;
  bool bin;
  int buffSize;
  char *buff;
  const int buffStep;
  FILE *file;
  
};

#endif
