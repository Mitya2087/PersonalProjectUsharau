#include "CalculatorEngine.h"
#include "ExpressionEvaluator.h"
#include "MathUtils.h"
#include <iomanip>
#include <sstream>

CalculatorEngine::CalculatorEngine()
    : lastResult_(0.0), hasError_(false), justCalculated_(false) {}

void CalculatorEngine::inputDigit(int digit) {
  clearError();
  if (justCalculated_) {
    currentInput_.clear();
    currentExpression_.clear();
    justCalculated_ = false;
  }
  currentInput_ += std::to_string(digit);
}

void CalculatorEngine::inputDecimalPoint() {
  clearError();
  if (justCalculated_) {
    currentInput_ = "0";
    currentExpression_.clear();
    justCalculated_ = false;
  }
  if (currentInput_.empty()) {
    currentInput_ = "0";
  }
  if (currentInput_.find('.') == std::string::npos) {
    currentInput_ += '.';
  }
}

void CalculatorEngine::inputOperator(char op) {
  clearError();
  if (!currentInput_.empty() || !currentExpression_.empty()) {
    if (!currentInput_.empty()) {
      currentExpression_ += currentInput_;
      currentInput_.clear();
    }
    currentExpression_ += " ";
    currentExpression_ += op;
    currentExpression_ += " ";
    justCalculated_ = false;
  }
}

void CalculatorEngine::inputFunction(const std::string &func) {
  clearError();

  if (!currentInput_.empty()) {
    currentExpression_ += func + "(" + currentInput_ + ")";
    currentInput_.clear();
  } else {
    currentExpression_ += func + "(";
  }

  justCalculated_ = false;
}

void CalculatorEngine::inputExpression(const std::string &expr) {
  clearError();
  currentExpression_ = expr;
  currentInput_.clear();
}

void CalculatorEngine::calculate() {
  clearError();

  std::string fullExpr = currentExpression_;
  if (!currentInput_.empty()) {
    fullExpr += currentInput_;
  }

  if (fullExpr.empty()) {
    return;
  }

  try {
    double result = ExpressionEvaluator::evaluate(fullExpr);
    lastResult_ = result;

    addToHistory(fullExpr, result);

    std::ostringstream oss;
    oss << std::setprecision(10) << result;
    currentInput_ = oss.str();
    currentExpression_.clear();
    justCalculated_ = true;

  } catch (const std::exception &e) {
    setError(e.what());
  }
}

void CalculatorEngine::clear() {
  currentInput_.clear();
  currentExpression_.clear();
  clearError();
  justCalculated_ = false;
}

void CalculatorEngine::clearEntry() {
  currentInput_.clear();
  clearError();
}

void CalculatorEngine::backspace() {
  if (!currentInput_.empty() && !justCalculated_) {
    currentInput_.pop_back();
  }
}

void CalculatorEngine::negate() {
  if (!currentInput_.empty()) {
    if (currentInput_[0] == '-') {
      currentInput_ = currentInput_.substr(1);
    } else {
      currentInput_ = "-" + currentInput_;
    }
  }
}

void CalculatorEngine::percent() {
  if (!currentInput_.empty()) {
    try {
      double val = std::stod(currentInput_);
      val /= 100.0;
      std::ostringstream oss;
      oss << std::setprecision(10) << val;
      currentInput_ = oss.str();
    } catch (...) {
      setError("Invalid number");
    }
  }
}

std::string CalculatorEngine::getDisplay() const {
  if (hasError_) {
    return "Error: " + errorMessage_;
  }
  if (!currentInput_.empty()) {
    return currentInput_;
  }
  if (!currentExpression_.empty()) {
    return currentExpression_;
  }
  return "0";
}

std::string CalculatorEngine::getCurrentExpression() const {
  std::string expr = currentExpression_;
  if (!currentInput_.empty()) {
    expr += currentInput_;
  }
  return expr;
}

bool CalculatorEngine::hasError() const { return hasError_; }

std::string CalculatorEngine::getErrorMessage() const { return errorMessage_; }

void CalculatorEngine::addToHistory(const std::string &expr, double result) {
  history_.emplace_back(expr, result);
}

std::vector<std::pair<std::string, double>>
CalculatorEngine::getHistory() const {
  return history_;
}

void CalculatorEngine::clearHistory() { history_.clear(); }

void CalculatorEngine::setError(const std::string &msg) {
  hasError_ = true;
  errorMessage_ = msg;
}

void CalculatorEngine::clearError() {
  hasError_ = false;
  errorMessage_.clear();
}
