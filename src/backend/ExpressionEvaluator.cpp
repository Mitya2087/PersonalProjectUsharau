#include "ExpressionEvaluator.h"
#include "MathUtils.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <stdexcept>

double ExpressionEvaluator::evaluate(const std::string &expression) {
  auto tokens = tokenize(expression);
  auto rpn = toRPN(tokens);
  return evaluateRPN(rpn);
}

std::vector<std::string>
ExpressionEvaluator::tokenize(const std::string &expr) {
  std::vector<std::string> tokens;
  std::string current;

  for (size_t i = 0; i < expr.length(); ++i) {
    char c = expr[i];

    if (std::isspace(c))
      continue;

    if (std::isdigit(c) || c == '.') {
      current += c;
    } else if (std::isalpha(c)) {
      current += c;
    } else {
      if (!current.empty()) {
        tokens.push_back(current);
        current.clear();
      }
      tokens.push_back(std::string(1, c));
    }
  }

  if (!current.empty()) {
    tokens.push_back(current);
  }

  return tokens;
}

std::vector<std::string>
ExpressionEvaluator::toRPN(const std::vector<std::string> &tokens) {
  std::vector<std::string> output;
  std::stack<std::string> operators;

  for (const auto &token : tokens) {
    if (std::isdigit(token[0]) ||
        (token.length() > 1 && token[0] == '-' && std::isdigit(token[1]))) {
      output.push_back(token);
    } else if (isFunction(token)) {
      operators.push(token);
    } else if (token == "(") {
      operators.push(token);
    } else if (token == ")") {
      while (!operators.empty() && operators.top() != "(") {
        output.push_back(operators.top());
        operators.pop();
      }
      if (!operators.empty())
        operators.pop();
      if (!operators.empty() && isFunction(operators.top())) {
        output.push_back(operators.top());
        operators.pop();
      }
    } else if (isOperator(token)) {
      while (!operators.empty() && operators.top() != "(" &&
             precedence(operators.top()) >= precedence(token)) {
        output.push_back(operators.top());
        operators.pop();
      }
      operators.push(token);
    }
  }

  while (!operators.empty()) {
    output.push_back(operators.top());
    operators.pop();
  }

  return output;
}

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
        // Convert degrees to radians for user convenience
        values.push(MathUtils::my_sin(MathUtils::to_radians(val)));
      else if (token == "cos")
        values.push(MathUtils::my_cos(MathUtils::to_radians(val)));
      else if (token == "tan")
        values.push(MathUtils::my_tan(MathUtils::to_radians(val)));
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

int ExpressionEvaluator::precedence(const std::string &op) {
  if (op == "+" || op == "-")
    return 1;
  if (op == "*" || op == "/")
    return 2;
  if (op == "^")
    return 3;
  return 0;
}

bool ExpressionEvaluator::isOperator(const std::string &token) {
  return token == "+" || token == "-" || token == "*" || token == "/" ||
         token == "^";
}

bool ExpressionEvaluator::isFunction(const std::string &token) {
  return token == "sqrt" || token == "sin" || token == "cos" ||
         token == "tan" || token == "log" || token == "exp";
}
