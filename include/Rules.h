#ifndef _INTER_CPP_RULES_H
#define _INTER_CPP_RULES_H
#include <map>
#include "Tokenizer.h"
#include "File.h"
#include "Production.h"

class Rules {
 public:
  Rules(File &file);
  Production *getProduction(string name);
  bool parse(const char *arg, string prod);

 private:
  Tokenizer tz;
  std::map<string, string> prodList;
  std::map<string, Production *> prods;

  void parse();
  void compile();
};

#endif
