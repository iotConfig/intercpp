#include "RegularEx.h"
#include <iostream>

using namespace std;
void parse(RegularEx &regexp, char *str) {
  cout << "reg exp: " << str << "\t" << regexp.parse(str) << endl; 
}

void test (char *expr)
{
  RegularEx regexp(expr);
  cout << expr << endl;
  parse(regexp, "robert craig robert craig foo");
  parse(regexp, "abhabh");
  parse(regexp, "abhabhhhhhhhhhh");
  parse(regexp, "abh");
  parse(regexp, "abhhhhhhhhhhh");
  parse(regexp, "ababh");
}
int main(int argc, char *argv[])
{
  test("(robert craig )*foo");
  test("(abh)+");
  test("abh+");
  test("(abh+)|ab");
  test("((abh+)|ab)*");
  return 0;
}
