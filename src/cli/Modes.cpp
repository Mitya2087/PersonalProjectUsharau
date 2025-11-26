#include "Modes.h"
#include "../backend/MathUtils.h"
#include <bitset>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

void StandardMode::run() {
  double a, b;
  char op;
  std::cout << "--- Standard Mode ---\n";
  std::cout << "Enter expression (e.g., 2 + 2) or 'q' to quit: ";

  while (true) {
    std::cout << "\n> ";
    if (!(std::cin >> a)) {
      std::cin.clear();
      std::string s;
      std::cin >> s;
      if (s == "q")
        break;
      std::cout << "Invalid input.\n";
      continue;
    }

    std::cin >> op;
    if (op == 's') {
      try {
        std::cout << "= " << MathUtils::my_sqrt(a) << std::endl;
      } catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
      }
      continue;
    }

    std::cin >> b;

    try {
      switch (op) {
      case '+':
        std::cout << "= " << a + b << std::endl;
        break;
      case '-':
        std::cout << "= " << a - b << std::endl;
        break;
      case '*':
        std::cout << "= " << a * b << std::endl;
        break;
      case '/':
        if (b == 0)
          throw std::invalid_argument("Division by zero");
        std::cout << "= " << a / b << std::endl;
        break;
      default:
        std::cout << "Unknown operator.\n";
        break;
      }
    } catch (const std::exception &e) {
      std::cout << "Error: " << e.what() << std::endl;
    }
  }
}