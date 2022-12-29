#include "Production.h"
#include "CharStream.h"
#include "ParsingExpression.h"
#include "Context.h"
#include <iostream>

extern Operator  *AND;
extern Operator *OR;

Production::Production(string prod, Rules *rules):
  production(prod), exp(NULL), 
  rules(rules), execRules(NULL)
{
  compileExecutionRules ();
  tz = new Tokenizer(*(new CharStream(production.c_str())));
  tz->setSeparator(" \t\n");
  compileProduction();
}

void Production::compileExecutionRules()
{
  int pos = 0, i = 0, start = 0, end = 0;
  //Remove the Execution Rules.
  pos = production.find('{');
  if (pos != -1 && pos != 0 && production[pos] != '\\'){
    start = pos;
    i ++;
  }else {
    return;
  }
  while ((pos = production.find('}')) != 0 || 
	 (pos = production.find('{')) != 0){
    if (production[pos - 1] == '\\')
      continue;
    if (production[pos] == '{'){
      i++;
    }else {
      if (--i==0){
	end = pos;
	break;
      }
    }
  }
  if (start != -1){
    string tmp = production;
    production = tmp.substr(0, start);
    if (end != -1)
      production += tmp.substr(end + 1, tmp.size());
    execRules = new ExecutionRules(tmp.substr(start + 1, end - start - 1));
  }
}

void Production::compileProduction()
{
  string token;
  Operator *op = NULL;
  while( (token = tz->nextToken()).size() != 0){
    int len = token.size();
    bool regExp = false, unspec = false, prod = false, stringP=false;
    int regExpStart = 0, prodStart = -1;
    
    for (int i = 0; i < len; i++){
      if (!unspec){
	switch (token[i]){
	case '\"':
	  if (regExp){
	    regExp = false;
	    string buff = token.substr(regExpStart, i - regExpStart);
	    RegularEx r(buff.c_str());
	    addExpression(r.expression, &op);
	  }else {
	    if (i != 0 && prodStart != -1){
	      Production *production = rules->getProduction(token.substr(prodStart, i - 1));
	      if (production != NULL)
		addExpression(production, &op);
	      prodStart = -1;
	      prod = false;
	    }
	    regExpStart = i + 1;
	    regExp = true;
	  }
	  break;
	case '\\':
	  unspec = true;
	  break;
	case '|':
	  op = OR;
	  break;
	case '/':
	  if (regExp){
	    regExp = false;
	    string buff = token.substr(regExpStart, i - regExpStart);
	    RegularEx r(buff.c_str());
	    addExpression(r.expression, &op);
	  } else {
	    regExpStart = i + 1;
	    regExp = true;
	  }
	  break;
	default:
	  if (!prod && !regExp){
	    prod = true;
	    prodStart = i;
	  }
	}
      }
    }
    if (prodStart != -1){
      Production *production = rules->getProduction(token.substr(prodStart, token.size()));
      addExpression(production, &op);
    }
  }
}

void Production::addExpression(Expression *expression, Operator **op)
{
  if (exp == NULL)
    exp = expression;
  else if (*op != NULL){
    exp = new ComplexExpression(exp, *op, expression);
    *op = NULL;
  }else
    exp = new ComplexExpression(exp, AND, expression);
}

bool Production::match(char **arg) const {
  if (exp != NULL){
    bool result = exp->match((char **)arg);
    if (result && execRules){
      Context c;
      execRules->execute(c);
    }
    return result;
  }
  else
    return false;
}
