#ifndef CALCULATORAPP_H
#define CALCULATORAPP_H

#include "../backend/History.h"
#include <memory>

class Mode;

class CalculatorApp {
public:
  CalculatorApp();
  ~CalculatorApp();

  void run();

private:
  void displayMainMenu();
  void handleModeSelection(int choice);
  void evaluateExpression();
  void manageHistory();
  void sortArrays();

  History history_;
};

#endif
