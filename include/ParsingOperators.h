#ifndef CPP_INTER_PARSING_OPS
#define CPP_INTER_PARSING_OPS

#include <string>

class Expression;
/*******************************************************************************
 **                                                                           **
 ** 
 **                                                                           **
 *******************************************************************************/
class Operator {
 public:
  virtual bool apply(const Expression *right, 
		     const Expression *left, 
		     char **str) const = 0;
};

class OperatorAND : public Operator
{
 public:
  bool apply(const Expression *right, 
	     const Expression *left, 
	     char **str) const;
};

class OperatorOR : public Operator
{
 public:
  bool apply(const Expression *right, 
	     const Expression *left, 
	     char **str) const;
};

class OperatorONE : public Operator
{
 public:
  bool apply(const Expression *right, 
	     const Expression *left, 
	     char **str) const;
};

class OperatorSTAR : public Operator
{
 public:
  bool apply(const Expression *right, 
	     const Expression *left, 
	     char **str) const;
};

class OperatorPLUS : public Operator
{
 public:
  bool apply(const Expression *right, 
	     const Expression *left, 
	     char **str) const;
};

#endif
