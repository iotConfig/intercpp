#include "Tokenizer.h"

Tokenizer::Tokenizer(Stream &st): 
  stream(st)
{}

void Tokenizer::setSeparator(char *tab)
{
  separator = tab;
}

string Tokenizer::nextToken(){
  string buff;
  char current = 0;
  bool unsep = false, unspec = false;
  while ((current = stream.next()) != 0){
    if (current == '\"' && !unspec)
      if (unsep)
	unsep = false;
      else
	unsep = true;
    if (current == '\\')
      unspec = true;
    else 
      unspec = false;
    if (!isSeparator(current) || unsep){
      buff += current;
    }else {
      if (buff.size() != 0)
	break;
    }
  }
  return buff;
}

bool Tokenizer::isSeparator(char c)
{
  int len = strlen(separator);
  for(int i = 0; i < len; i++)
    if (separator[i] == c)
      return true;
  return false;
}
