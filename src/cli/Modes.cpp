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
  std::cout << "Supported operations:\n";
  std::cout << "  &   - AND         Example: 12 & 10\n";
  std::cout << "  |   - OR          Example: 12 | 10\n";
  std::cout << "  ^   - XOR         Example: 12 ^ 10\n";
  std::cout << "  ~   - NOT         Example: ~ 12\n";
  std::cout << "  <<  - Shift left  Example: 3 << 2\n";
  std::cout << "  >>  - Shift right Example: 12 >> 2\n";
  std::cout << "\nOr just enter a number to see it in DEC, HEX, BIN\n";
  std::cout << "Type 'q' or 'quit' to return to main menu.\n\n";

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
      int result = evaluateBitwiseExpression(input);

      std::cout << "DEC: " << result << std::endl;
      std::cout << "HEX: " << toHex(result) << std::endl;
      std::cout << "BIN: " << toBinary(result) << std::endl;

      if (history) {
        history->addEntry(input, static_cast<double>(result));
      }
    } catch (const std::exception &e) {
      std::cout << "Error: " << e.what() << std::endl;
      std::cout << "Tip: Use format like '3 << 2' or '12 & 10' or just '15'\n";
    }
  }
}

int ProgrammerMode::evaluateBitwiseExpression(const std::string &expr) {
  std::istringstream iss(expr);
  std::string token1, op, token2;

  // Try to parse as: number operator number
  if (iss >> token1) {
    // Check if it's just a number (for conversion)
    if (!(iss >> op)) {
      return parseNumber(token1);
    }

    if (op == "~") {
      int a = parseNumber(token1 == "~" ? "" : token1);
      if (token1 == "~") {
        iss.str(expr.substr(1));
        iss.clear();
        iss >> token1;
        a = parseNumber(token1);
      }
      return ~a;
    }

    // Binary operation
    if (!(iss >> token2)) {
      throw std::runtime_error("Missing second operand");
    }

    int a = parseNumber(token1);
    int b = parseNumber(token2);

    if (op == "&")
      return a & b;
    if (op == "|")
      return a | b;
    if (op == "^")
      return a ^ b;
    if (op == "<<")
      return a << b;
    if (op == ">>")
      return a >> b;

    throw std::runtime_error("Unknown operator: " + op);
  }

  throw std::runtime_error("Invalid expression format");
}

int ProgrammerMode::parseNumber(const std::string &str) {
  if (str.empty()) {
    throw std::runtime_error("Empty number");
  }

  // Check for hex (0x prefix)
  if (str.length() > 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
    return std::stoi(str, nullptr, 16);
  }

  // Check for binary (0b prefix)
  if (str.length() > 2 && str[0] == '0' && (str[1] == 'b' || str[1] == 'B')) {
    return std::stoi(str.substr(2), nullptr, 2);
  }

  // Decimal
  return std::stoi(str);
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
