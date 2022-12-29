#ifndef CPP_INTER_PARSER
#define CPP_INTER_PARSER

#include <map>

class Parser {

 public:
  Parser(File &f);
  Parser(const char *string);

 private:
  map<string,Production> prod;
  map<string, vector<token> > tokens;

};
#endif
