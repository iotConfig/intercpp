#ifndef CPP_INT_EXCEPTION
#define CPP_INT_EXCEPTION

#include <exception>
using namespace std;

class NullPointerException : public exception {};
class FileOpeningFailure : public exception{
 public:
  FileOpeningFailure(const char *fileName){}
};

#endif
