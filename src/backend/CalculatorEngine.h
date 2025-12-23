#ifndef CALCULATORENGINE_H
#define CALCULATORENGINE_H

#include <string>
#include <vector>

class CalculatorEngine {
public:
  CalculatorEngine();

  void inputDigit(int digit);
  void inputDecimalPoint();
  void inputOperator(char op);
  void inputFunction(const std::string &func);
  void inputExpression(const std::string &expr);

  void calculate();
  void clear();
  void clearEntry();
  void backspace();
  void negate();
  void percent();

  std::string getDisplay() const;
  std::string getCurrentExpression() const;
  bool hasError() const;
  std::string getErrorMessage() const;

  void addToHistory(const std::string &expr, double result);
  std::vector<std::pair<std::string, double>> getHistory() const;
  void clearHistory();

private:
  std::string currentInput_;
  std::string currentExpression_;
  double lastResult_;
  bool hasError_;
  std::string errorMessage_;
  bool justCalculated_;
  std::vector<std::pair<std::string, double>> history_;

  void setError(const std::string &msg);
  void clearError();
};

#endif
