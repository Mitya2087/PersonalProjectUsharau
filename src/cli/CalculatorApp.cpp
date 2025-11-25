#include "CalculatorApp.h"
#include "ExpressionEvaluator.h"
#include "Modes.h"
#include "Sorter.h"
#include <iostream>
#include <limits>
#include <memory>

CalculatorApp::CalculatorApp() {}

CalculatorApp::~CalculatorApp() {}

void CalculatorApp::run() {
  std::cout << "=== Extended Calculator ===\n";
  std::cout << "Author: Usharov Dmitriy Pavlovich, Group 1\n\n";

  while (true) {
    displayMainMenu();

    int choice;
    std::cin >> choice;

    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input. Try again.\n";
      continue;
    }

    if (choice == 0) {
      std::cout << "Exiting calculator. Goodbye!\n";
      break;
    }

    handleModeSelection(choice);
  }
}

void CalculatorApp::displayMainMenu() {
  std::cout << "\n=== Main Menu ===\n";
  std::cout << "1. Standard Mode\n";
  std::cout << "2. Scientific Mode\n";
  std::cout << "3. Programmer Mode\n";
  std::cout << "4. Evaluate Expression (RPN)\n";
  std::cout << "5. History Management\n";
  std::cout << "6. Array Sorting\n";
  std::cout << "0. Exit\n";
  std::cout << "> ";
}

void CalculatorApp::handleModeSelection(int choice) {
  std::unique_ptr<Mode> mode;

  switch (choice) {
  case 1:
    mode = std::make_unique<StandardMode>();
    mode->run();
    break;
  case 2:
    mode = std::make_unique<ScientificMode>();
    mode->run();
    break;
  case 3:
    mode = std::make_unique<ProgrammerMode>();
    mode->run();
    break;
  case 4:
    evaluateExpression();
    break;
  case 5:
    manageHistory();
    break;
  case 6:
    sortArrays();
    break;
  default:
    std::cout << "Invalid choice.\n";
  }
}

void CalculatorApp::evaluateExpression() {
  std::cout << "--- Expression Evaluator ---\n";
  std::cout << "Enter expression (e.g., 2 + 3 * 4, sqrt(16), sin(0.5))\n";
  std::cout << "Enter 'q' to quit.\n";

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  while (true) {
    std::cout << "\n> ";
    std::string expr;
    std::getline(std::cin, expr);

    if (expr == "q")
      break;

    try {
      double result = ExpressionEvaluator::evaluate(expr);
      std::cout << "= " << result << std::endl;
      history_.addEntry(expr, result);
    } catch (const std::exception &e) {
      std::cout << "Error: " << e.what() << std::endl;
    }
  }
}

void CalculatorApp::manageHistory() {
  while (true) {
    std::cout << "\n--- History Management ---\n";
    std::cout << "1. Display history\n";
    std::cout << "2. Undo\n";
    std::cout << "3. Redo\n";
    std::cout << "4. Save to file\n";
    std::cout << "5. Load from file\n";
    std::cout << "6. Clear history\n";
    std::cout << "0. Back to main menu\n";
    std::cout << "> ";

    int choice;
    std::cin >> choice;

    if (choice == 0)
      break;

    switch (choice) {
    case 1:
      history_.display();
      break;
    case 2:
      history_.undo();
      break;
    case 3:
      history_.redo();
      break;
    case 4: {
      std::string filename;
      std::cout << "Enter filename: ";
      std::cin >> filename;
      history_.save(filename);
      break;
    }
    case 5: {
      std::string filename;
      std::cout << "Enter filename: ";
      std::cin >> filename;
      history_.load(filename);
      break;
    }
    case 6:
      history_.clear();
      break;
    default:
      std::cout << "Invalid choice.\n";
    }
  }
}

void CalculatorApp::sortArrays() { Sorter::runInteractive(); }
