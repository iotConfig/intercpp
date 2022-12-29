#include <iostream>
#include "File.h"

int main(int argc, char *argv[]){
  
  File file(argv[1], "r");
  char *buff = file.readLine();
  while (buff != NULL){
    cout << buff << endl;
    buff = file.readLine();
  }
  return 0;
}



