#include "ParsingExpressions.h"
#include "ParsingOperators.h"

bool OperatorAND::apply(const Expression *left, 
			const Expression *right, 
			char **str) const
{
  return left->match(str) && right->match(str);
}

bool OperatorOR::apply(const Expression *left, 
			const Expression *right, 
			char **str) const
{
  char *save = *str;
  int leftPos = -1;
  if (left->match(str))
    leftPos = *str - save;
  *str =save;
  if (right->match(str)){
   if ((*str - save) > leftPos)
     return true;
   else{
     *str = save + leftPos;
     return true;
   }
  } else {
    if (leftPos != -1){
      *str = save + leftPos;
      return true;
    }
    return false;
  }
}

bool OperatorSTAR::apply(const Expression *left, 
			const Expression *    , 
			char **str) const
{
  char *pos = *str;
  bool cont = true;
  while (left->match(str) && cont){
    cont = pos != *str;
    pos = *str;
  }
  return true;
}

bool OperatorONE::apply(const Expression *left, 
			const Expression *    , 
			char **str) const
{
  left->match(str);
  return true;
}

bool OperatorPLUS::apply(const Expression *left, 
			const Expression *    , 
			char **str) const
{
  char *pos = *str;
  bool cont = true;
  bool ret = false;
  while (left->match(str) && cont){
    ret =true;
    cont = pos != *str;
    pos = *str;
  }
  return ret;
}


