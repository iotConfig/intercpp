#include <iostream>
#include "Rules.h"
#include "CharStream.h"
typedef map<string, string>::iterator prodListIt;
typedef map<string, Production *>::iterator prodIt;
Rules::Rules(File &file):
  tz(file)
{
  parse();
  compile();
}

void Rules::parse()
{
  tz.setSeparator("#");
  string token;
  while ((token = tz.nextToken()).size() != 0){
    CharStream stream(token.c_str());
    Tokenizer tmpTok(stream);
    tmpTok.setSeparator("\n:");
    string name = tmpTok.nextToken();
    tmpTok.setSeparator(":");
    string prod = tmpTok.nextToken(); 
    if (name.size () != 0 && prod.size() != 0){
      std::map<string, string>::value_type value(name, prod);
      std::cout << "Name:" << name << " prod:" << prod << endl;
      prodList.insert(value);
    }
  }
}

void Rules::compile(){
  for (prodListIt it = prodList.begin(); it != prodList.end(); it++){
    std::map<string, Production *>::value_type val((*it).first,
						   new Production((*it).second, this));
    prods.insert(val);
  }
  
}

Production *Rules::getProduction(string name){
  prodIt it = prods.find(name);
  if (it != prods.end())
    return (*it).second;
  prodListIt its = prodList.find(name);
  if (its == prodList.end())
    return NULL;
  std::map<string, Production *>::value_type val((*its).first,
						 new Production((*its).second.c_str(), this));
  prods.insert(val);
  return val.second;
}

bool Rules::parse(const char *arg, string prod){
  prodIt it = prods.find(prod);
  if (it != prods.end())
    return (*it).second->match((char **)&arg);
  else 
    return false;
}

