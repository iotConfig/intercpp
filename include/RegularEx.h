#ifndef CPP_INTER_REGULAR_EX
#define CPP_INTER_REGULAR_EX

#include "string.h"
#include "ParsingExpressions.h"

/*******************************************************************************
 **                                                                           **
 ** This Class represents the regular expression. It builds an regular        **
 ** expression tree to reduce it to atomic parsing rules.                     **
 ** Once an regular expression has been compile (building the tree) strings   **
 ** can be parsed using the parse method.
 **                                                                           **
 *******************************************************************************/

class RegularEx {
  
 public:
  RegularEx(const char *reg);
  void compile();
  bool parse(char *str);

 private:
  const char *regexp;
  Expression *expression, *current, *tmp;
  Operator *op;
  Expression *appExpression(Expression *left,
			    Expression *right,
			    Operator *op);
  void oneOperator(char *, int &, Operator*);
  friend class Production;
};

#endif
