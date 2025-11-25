#include "ExpressionEvaluator.h"
#include "MathUtils.h"
#include <cctype>
#include <stdexcept>

double ExpressionEvaluator::evaluateRPN(const std::vector<std::string> &rpn) {
  std::stack<double> values;

  for (const auto &token : rpn) {
    if (std::isdigit(token[0]) ||
        (token.length() > 1 && token[0] == '-' && std::isdigit(token[1]))) {
      values.push(std::stod(token));
    } else if (isFunction(token)) {
      if (values.empty())
        throw std::runtime_error("Invalid expression");
      double val = values.top();
      values.pop();

      if (token == "sqrt")
        values.push(MathUtils::my_sqrt(val));
      else if (token == "sin")
        values.push(MathUtils::my_sin(val));
      else if (token == "cos")
        values.push(MathUtils::my_cos(val));
      else if (token == "tan")
        values.push(MathUtils::my_tan(val));
      else if (token == "log")
        values.push(MathUtils::my_log(val));
      else if (token == "exp")
        values.push(MathUtils::my_exp(val));
    } else if (isOperator(token)) {
      if (values.size() < 2)
        throw std::runtime_error("Invalid expression");
      double b = values.top();
      values.pop();
      double a = values.top();
      values.pop();

      if (token == "+")
        values.push(a + b);
      else if (token == "-")
        values.push(a - b);
      else if (token == "*")
        values.push(a * b);
      else if (token == "/") {
        if (b == 0)
          throw std::runtime_error("Division by zero");
        values.push(a / b);
      } else if (token == "^")
        values.push(MathUtils::my_pow(a, b));
    }
  }

  if (values.size() != 1)
    throw std::runtime_error("Invalid expression");
  return values.top();
}

bool ExpressionEvaluator::isOperator(const std::string &token) {
  return token == "+" || token == "-" || token == "*" || token == "/" ||
         token == "^";
}

bool ExpressionEvaluator::isFunction(const std::string &token) {
  return token == "sqrt" || token == "sin" || token == "cos" ||
         token == "tan" || token == "log" || token == "exp";
}