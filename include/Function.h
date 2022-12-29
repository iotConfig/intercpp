#ifndef _INTER_CPP_FUNCTION_
#define _INTER_CPP_FUNCTION_

#include "Context.h"

class function {
 public:
  Function(string name, Context &ct) : funcName(name) 
  {}
  virtual void operator() = 0;

 private:
  string funcName;
};

#endif
