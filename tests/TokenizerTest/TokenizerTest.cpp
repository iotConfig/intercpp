#include <iostream>
#include "File.h"
#include "Tokenizer.h"

int main(int argc, char *argv[]){
  
  File f(argv[1], "r");
  Tokenizer tokenizer(f);
  tokenizer.setSeparator(" .;:\n");
  char *token = NULL;
  while((token = tokenizer.nextToken()) != NULL){
    cout << token << endl;
  }
  return 0;
}
