#include "Modes.h"
#include "../backend/ExpressionEvaluator.h"
#include "../backend/History.h"
#include <bitset>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

void StandardMode::run(History *history) {
  std::cout << "\n=== Standard Mode ===\n";
  std::cout << "Enter arithmetic expressions.\n";
  std::cout << "Supported: +, -, *, /, sqrt(), parentheses\n";
  std::cout << "Examples:\n";
  std::cout << "  2 + 2 * 3\n";
  std::cout << "  (10 + 5) / 3\n";
  std::cout << "  sqrt(144)\n";
  std::cout << "\nType 'q' or 'quit' to return to main menu.\n\n";

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  while (true) {
    std::cout << "std> ";
    std::string input;
    std::getline(std::cin, input);

    // Trim whitespace
    input.erase(0, input.find_first_not_of(" \t\n\r"));
    input.erase(input.find_last_not_of(" \t\n\r") + 1);

    if (input == "q" || input == "quit" || input.empty()) {
      break;
    }

    try {
      double result = ExpressionEvaluator::evaluate(input);
      std::cout << "= " << result << std::endl;
      if (history) {
        history->addEntry(input, result);
      }
    } catch (const std::exception &e) {
      std::cout << "Error: " << e.what() << std::endl;
    }
  }
}

void ScientificMode::run(History *history) {
  std::cout << "\n=== Scientific Mode ===\n";
  std::cout << "Enter mathematical expressions with scientific functions.\n";
  std::cout
      << "Available functions: sin, cos, tan, sqrt, log, exp, ^ (power)\n";
  std::cout << "Note: Trig functions use DEGREES\n";
  std::cout << "Examples:\n";
  std::cout << "  sin(90)           - sine of 90 degrees\n";
  std::cout << "  sqrt(16) + 5      - square root plus 5\n";
  std::cout << "  2^8               - 2 to the power of 8\n";
  std::cout << "  log(100) * 2      - logarithm times 2\n";
  std::cout << "  (sin(30) + cos(60)) / 2\n";
  std::cout << "\nType 'q' or 'quit' to return to main menu.\n\n";

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  while (true) {
    std::cout << "sci> ";
    std::string input;
    std::getline(std::cin, input);

    // Trim whitespace
    input.erase(0, input.find_first_not_of(" \t\n\r"));
    input.erase(input.find_last_not_of(" \t\n\r") + 1);

    if (input == "q" || input == "quit" || input.empty()) {
      break;
    }

    try {
      double result = ExpressionEvaluator::evaluate(input);
      std::cout << "= " << result << std::endl;
      if (history) {
        history->addEntry(input, result);
      }
    } catch (const std::exception &e) {
      std::cout << "Error: " << e.what() << std::endl;
      std::cout << "Tip: Use sin(), cos(), tan(), sqrt(), log(), exp(), ^ for "
                   "power\n";
    }
  }
}

void ProgrammerMode::run(History *history) {
  std::cout << "\n=== Programmer Mode ===\n";
  std::cout << "Bitwise operations and base conversions.\n";
  std::cout << "Commands:\n";
  std::cout << "  AND, OR, XOR, NOT    - Bitwise operations\n";
  std::cout << "  << >>                - Bit shifts\n";
  std::cout << "  OR enter any number/expression to see in BIN, DEC, HEX\n";
  std::cout << "\nType 'q' or 'quit' to return to main menu.\n\n";

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  while (true) {
    std::cout << "prog> ";
    std::string input;
    std::getline(std::cin, input);

    // Trim whitespace
    input.erase(0, input.find_first_not_of(" \t\n\r"));
    input.erase(input.find_last_not_of(" \t\n\r") + 1);

    if (input == "q" || input == "quit" || input.empty()) {
      break;
    }

    try {
      // Check if it's a bitwise operation command
      if (input == "AND" || input == "OR" || input == "XOR" || input == "NOT" ||
          input == "<<" || input == ">>") {
        handleBitwiseOperation(input);
      } else {
        // Try to evaluate as expression or number
        double result = ExpressionEvaluator::evaluate(input);
        int intResult = static_cast<int>(result);

        std::cout << "DEC: " << intResult << std::endl;
        std::cout << "HEX: " << toHex(intResult) << std::endl;
        std::cout << "BIN: " << toBinary(intResult) << std::endl;
      }
    } catch (const std::exception &e) {
      std::cout << "Error: " << e.what() << std::endl;
      std::cout << "Tip: Use AND, OR, XOR, NOT, <<, >> for bitwise ops\n";
    }
  }
}

void ProgrammerMode::handleBitwiseOperation(const std::string &op) {
  int a, b = 0;
  std::cout << "Enter first number: ";
  std::cin >> a;
  std::cin.ignore();

  if (op != "NOT") {
    std::cout << "Enter second number: ";
    std::cin >> b;
    std::cin.ignore();
  }

  int result;
  if (op == "AND") {
    result = a & b;
  } else if (op == "OR") {
    result = a | b;
  } else if (op == "XOR") {
    result = a ^ b;
  } else if (op == "NOT") {
    result = ~a;
  } else if (op == "<<") {
    result = a << b;
  } else if (op == ">>") {
    result = a >> b;
  } else {
    throw std::runtime_error("Unknown operation");
  }

  std::cout << "Result:\n";
  std::cout << "  DEC: " << result << std::endl;
  std::cout << "  HEX: " << toHex(result) << std::endl;
  std::cout << "  BIN: " << toBinary(result) << std::endl;
}

std::string ProgrammerMode::toBinary(long long n) {
  return std::bitset<32>(n).to_string();
}

std::string ProgrammerMode::toHex(long long n) {
  std::stringstream ss;
  ss << std::hex << std::uppercase << n;
  return "0x" + ss.str();
}

long long ProgrammerMode::fromBinary(std::string s) {
  return std::stoll(s, nullptr, 2);
}

long long ProgrammerMode::fromHex(std::string s) {
  return std::stoll(s, nullptr, 16);
}
