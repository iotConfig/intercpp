#ifndef CPP_INTER_PARSING_EXP
#define CPP_INTER_PARSING_EXP

#include <string>

class Operator;

class Expression {
  
 public:
  virtual bool match(char **str) const = 0;

};

class TrueExpression : public Expression {
 public:
  bool match(char **str) const;
};

class SimpleExpression : public Expression {
 public:
  SimpleExpression(const char *exp);
  bool match(char **str) const ;

 private:
  const char *exp;
  int expLen;
};

class ComplexExpression : public Expression {
  
 public:
  ComplexExpression (const Expression *left, 
		     const Operator *op = NULL, 
		     const Expression *right = NULL);
  bool match(char **str) const;
  
 private:
  
  const Expression *left;
  const Expression *right;
  const Operator *op;
  
};

class RangeExpression :public Expression {

 public:
  RangeExpression(char start, char end);
  bool match(char **str) const;

 private:
  
  char start, end;

};
#endif
