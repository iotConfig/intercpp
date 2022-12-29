#ifndef CPP_INTER_PRODUCTION
#define CPP_INTER_PRODUCTION
#include <map>
#include <vector>
#include "RegularEx.h"
#include "Tokenizer.h"
#include "ParsingExpression.h"
#include "ParsingOperators.h"
#include "ExecutionRules.h"
#include "Rules.h"
/****************************************************************
 ** Production is a regular expression that can execute rules.
 **
 ****************************************************************/

class Rules;

class Production : public Expression {

 public:
  Production(string production, Rules *rules);
  bool match(char **arg) const;

 private:
  string production;
  Expression *exp;
  Rules *rules;
  ExecutionRules *execRules;
  Tokenizer *tz;

  void addExpression(Expression *, Operator **);
  void execute();
  void compileProduction();
  void compileExecutionRules();
};

#endif
