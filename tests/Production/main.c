#include <iostream>
#include "Rules.h"
#include "Production.h"

int main(int argc, char **argv)
{
  File f(argv[1], "r");
  Rules r(f);
  cout << "going to parse \"" << argv[3] << "\" with " << argv[2] << endl;
  cout << "parsing Rule result=" << r.parse(argv[3], argv[2]) << endl;
  return 0;
}
