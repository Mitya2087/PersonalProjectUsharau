#ifndef EXPRESSIONEVALUATOR_H
#define EXPRESSIONEVALUATOR_H

#include <stack>
#include <string>
#include <vector>

class ExpressionEvaluator {
public:
  static double evaluate(const std::string &expression);

private:
  static std::vector<std::string> tokenize(const std::string &expr);
  static std::vector<std::string> toRPN(const std::vector<std::string> &tokens);
  static double evaluateRPN(const std::vector<std::string> &rpn);
  static int precedence(const std::string &op);
  static bool isOperator(const std::string &token);
  static bool isFunction(const std::string &token);
};

#endif
