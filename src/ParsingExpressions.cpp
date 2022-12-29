#include "ParsingExpressions.h"
#include "ParsingOperators.h"
#include <iostream>
using namespace std;

Operator  *OR = new OperatorOR();
Operator  *AND = new OperatorAND();
Operator  *STAR = new OperatorSTAR();
Operator *PLUS = new OperatorPLUS();
Operator *ONE = new OperatorONE();

RangeExpression::RangeExpression(char start, char end) :
  start(start), end(end)
{
  cout << this << ":re s(" << start << ") e(" << end << ")" << endl;
}

bool RangeExpression::match(char **str) const 
{
  if (**str >= start && **str <= end){
    *str++;
    return true;
  } else 
    return false;
}
SimpleExpression::SimpleExpression(const char *expr) : 
  expLen(strlen(expr))
{
  exp = new char[expLen + 1];
  strcpy((char *)exp, expr);
  cout << this << ":se " << exp << endl;
}

bool SimpleExpression::match (char **str) const 
{
  if (strncmp(exp, *str, expLen) == 0){
    *str += expLen;
    return true;
  } else
    return false;
}

ComplexExpression::ComplexExpression(const Expression *left,
				     const Operator *op,
				     const Expression *right) :
  left(left), right(right), op(op)
{
  char *opName = NULL;
  if (op == OR)
    opName = "OR";
  if (op == AND)
    opName = "AND";
  if (op == STAR)
    opName = "*";
  if (op == ONE)
    opName = "?";
  if (op == PLUS)
    opName = "+";

  cout << this << ":ce left:" << left << " right:" << right << " op:" << opName << endl;
}

bool ComplexExpression::match(char **str) const 
{
  if (op != NULL)
    return op->apply(left, right, str);
  else
    return right->match(str);
}

bool TrueExpression::match(char **str) const
{
  if (strlen (*str) > 1){
    (*str)++;
    return true;
  } else
    return false;
}
