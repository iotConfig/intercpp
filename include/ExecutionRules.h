#ifndef  CPP_INTER_EXECUTION_RULES
#define  CPP_INTER_EXECUTION_RULES

#include <string>
#include "Context.h"

class ExecutionRules {
 private:
  void init();
  std::string execRules;

 public:
  ExecutionRules(std::string exe);
  void execute(Context &c);
};

#endif
