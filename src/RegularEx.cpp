#include "RegularEx.h"
using namespace std;
#include <iostream>
#include <vector>
#include <string>
#include "ParsingOperators.h"

extern Operator  *OR;
extern Operator  *AND;
extern Operator  *STAR;
extern Operator *ONE;
extern Operator *PLUS;


RegularEx::RegularEx(const char *regexp) :
  regexp(regexp), expression(NULL), 
  current(NULL), tmp(NULL), op(NULL)
{
  compile();
}

void RegularEx::oneOperator(char *buff, int &index, Operator *oper)
{
  buff[index] = 0;
  if (index != 0){
    char c = buff[index - 1];
    if (index > 1) {
      buff[index - 1] = 0;
      if (op == NULL){
	current = appExpression(current,
				tmp,
				NULL);
	tmp = NULL;
      }
      tmp = appExpression(tmp,
			  new SimpleExpression(buff),
			  op);
      op = NULL;
      buff[0] = c;
      buff[1] = 0;
    } 
    tmp = appExpression(tmp, new ComplexExpression(new SimpleExpression(buff), 
						   oper),
			op);
  op = NULL;
  } else
    tmp = new ComplexExpression(tmp, oper);
  index = 0;
}
void RegularEx::compile()
{
  current = NULL;
  tmp = NULL;
  Operator *op = NULL;
  int len = strlen(regexp), index = 0;
  char buff[len + 1];
  bool unspec = false;
  for (int i = 0; i < len; i++){
    if (!unspec) {
      switch(regexp[i]){
      case '.':
	buff[index] = 0;
	index = 0;
	if (strlen(buff)){
	  tmp = appExpression(tmp, 
			      new SimpleExpression(buff),
			      op);
	op = NULL;
	}
	if (op == NULL){
	  current = appExpression(current, tmp, NULL);
	  tmp = NULL;
	} 
	tmp = appExpression(tmp, new TrueExpression(), op);
	op = NULL;
	break;
      case '\\':
	unspec = true;
	break;
      case '[':{
	buff[index]=0;
	index=0;
	if (strlen(buff)){
	  tmp = appExpression(tmp, 
			      new SimpleExpression(buff),
			      op);
	  op = NULL;
	}
	if (op == NULL){
	  current = appExpression(current, tmp, NULL);
	  tmp = NULL;
	} 
	char startChar = regexp[i+1];
	char endChar = regexp[i+3];
	i += 4;
	tmp = appExpression(tmp, new RangeExpression(startChar, endChar), op);
	op = NULL;
	break;
      }
      case '(':{
	char subRegExp[len - i + 1];
	int paramCount = 1, count2 = 0;
	bool unspec2 = false, finished = false;
	for(int j = 1; j < len && !finished; j++){
	  switch (regexp[i + j]) {
	  case '(':
	    if (!unspec2)
	      paramCount++;
	    break;
	  case ')':{
	    if (!unspec2)
	      paramCount--;
	    if (paramCount == 0){
	      subRegExp[count2] = 0;
	      RegularEx exp(subRegExp);
	      if (op == NULL){
		current = appExpression(current,
					tmp,
					NULL);
		tmp = NULL;
	      }
	      tmp = appExpression( tmp, exp.expression, op);
	      op = NULL;
	      finished = true;
	      i += j;
	      index = 0;
	      continue;
	    }
	    break;
	  }
	  case '\\':
	    unspec2 =true;
	    continue;
	    break;
	  }
	  subRegExp[count2++] = regexp[j + i];
	}
	break;
      }
      case '*':
	oneOperator(buff, index, STAR);
	break;
      case '+':
	oneOperator(buff, index, PLUS);
	break;
      case '?':
	oneOperator(buff, index, ONE);
	break;
      case '|':
	op = OR;
	break;
      default:
	buff[index++] = regexp[i];
      }
    } else {
      buff[index++] = regexp[i];
    }
  }

  current = appExpression(current,
			  tmp,
			  NULL);
  buff[index] = 0;
  if (strlen(buff))
    current = appExpression(current, 
			    new SimpleExpression(buff),
			    op);
  expression = current;
}

Expression *
RegularEx::appExpression(Expression *left,
			 Expression *right,
			 Operator *op)
{
  if (left != NULL) {
    if (right != NULL) {
      if (op == NULL) 
	return new ComplexExpression(left,
				     AND, 
				     right);
      else
	return new ComplexExpression(left, op, right);
    } else {
      if (op)
	return new ComplexExpression(left, op);
      return left;
    }
  } else {
    if (right != NULL) {
      if (op)
	return new ComplexExpression(right, op);
      return right;
    }
  }
  return NULL;
}

bool RegularEx::parse(char *str)
{
  return expression->match(&str) && strlen(str) == 0;
}
