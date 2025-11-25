#ifndef EXPRESSIONEVALUATOR_H
#define EXPRESSIONEVALUATOR_H

#include <stack>
#include <string>
#include <vector>

class ExpressionEvaluator {
private:
  static double evaluateRPN(const std::vector<std::string> &rpn);
  static bool isOperator(const std::string &token);
  static bool isFunction(const std::string &token);
};

#endif
