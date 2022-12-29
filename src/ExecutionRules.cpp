#include "ExecutionRules.h"
#include "Tokenizer.h"
#include "CharStream.h"
#include <iostream>
using namespace std;

//Execute a production rule i.e. in { }
void ExecutionRules::execute(Context &)
{
  CharStream st(execRules.c_str());
  Tokenizer tz(st);
  tz.setSeparator(" \t");
  string token;
  bool hadPrint = false;
  while( (token = tz.nextToken()).size() != 0){
    if (token == "print")
      hadPrint = true;
    if (hadPrint)
      cout << token << " ";
  }
  cout << endl;
}

void ExecutionRules::init()
{
  
}

ExecutionRules::ExecutionRules(string exec):
  execRules(exec)
{
  init();
}
