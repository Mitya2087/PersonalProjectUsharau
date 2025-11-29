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
    if (op == 's') { // sqrt special case: number s
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

void ScientificMode::run() {
  std::cout << "--- Scientific Mode ---\n";
  std::cout << "Supported operations: +, -, *, /, ^ (pow), s (sqrt), l (log), "
               "e (exp), S (sin), C (cos), T (tan)\n";
  std::cout << "Format: \n";
  std::cout << "  Binary: 2 + 2\n";
  std::cout << "  Unary: s 9 (sqrt(9)), S 30 (sin(30 deg))\n";
  std::cout << "Enter 'q' to quit.\n";

  while (true) {
    std::cout << "\n> ";
    std::string token;
    std::cin >> token;

    if (token == "q")
      break;

    // Check if unary operator
    if (token.length() == 1 &&
        std::string("sleSCT").find(token) != std::string::npos) {
      double val;
      std::cin >> val;
      try {
        switch (token[0]) {
        case 's':
          std::cout << "= " << MathUtils::my_sqrt(val) << std::endl;
          break;
        case 'l':
          std::cout << "= " << MathUtils::my_log(val) << std::endl;
          break;
        case 'e':
          std::cout << "= " << MathUtils::my_exp(val) << std::endl;
          break;
        case 'S':
          std::cout << "= " << MathUtils::my_sin(MathUtils::to_radians(val))
                    << std::endl;
          break;
        case 'C':
          std::cout << "= " << MathUtils::my_cos(MathUtils::to_radians(val))
                    << std::endl;
          break;
        case 'T':
          std::cout << "= " << MathUtils::my_tan(MathUtils::to_radians(val))
                    << std::endl;
          break;
        }
      } catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
      }
    } else {
      // Binary or number
      try {
        double a = std::stod(token);
        char op;
        std::cin >> op;
        double b;
        std::cin >> b;

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
        case '^':
          std::cout << "= " << MathUtils::my_pow(a, b) << std::endl;
          break;
        default:
          std::cout << "Unknown operator.\n";
          break;
        }
      } catch (...) {
        std::cout << "Invalid input format.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    }
  }
}

void ProgrammerMode::run() {
  std::cout << "--- Programmer Mode ---\n";
  std::cout << "Supported operations: &, |, ^ (XOR), ~ (NOT), <<, >>\n";
  std::cout << "Format: 5 & 3\n";
  std::cout << "Conversions: bin <num>, hex <num>, dec <num>\n";
  std::cout << "Enter 'q' to quit.\n";

  while (true) {
    std::cout << "\n> ";
    std::string first;
    std::cin >> first;

    if (first == "q")
      break;

    if (first == "bin") {
      long long val;
      std::cin >> val;
      std::cout << "= " << toBinary(val) << std::endl;
    } else if (first == "hex") {
      long long val;
      std::cin >> val;
      std::cout << "= " << toHex(val) << std::endl;
    } else if (first == "dec") {
      std::string val;
      std::cin >> val;
      // Try to detect format
      if (val.substr(0, 2) == "0x")
        std::cout << "= " << fromHex(val.substr(2)) << std::endl;
      else if (val.find_first_not_of("01") == std::string::npos)
        std::cout << "= " << fromBinary(val) << std::endl;
      else
        std::cout << "Unknown format" << std::endl;
    } else {
      try {
        long long a = std::stoll(first);
        std::string op;
        std::cin >> op;

        if (op == "~") {
          std::cout << "= " << (~a) << std::endl;
        } else {
          long long b;
          std::cin >> b;
          if (op == "&")
            std::cout << "= " << (a & b) << std::endl;
          else if (op == "|")
            std::cout << "= " << (a | b) << std::endl;
          else if (op == "^")
            std::cout << "= " << (a ^ b) << std::endl;
          else if (op == "<<")
            std::cout << "= " << (a << b) << std::endl;
          else if (op == ">>")
            std::cout << "= " << (a >> b) << std::endl;
          else
            std::cout << "Unknown operator\n";
        }
      } catch (...) {
        std::cout << "Invalid input.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    }
  }
}

std::string ProgrammerMode::toBinary(long long n) {
  return std::bitset<64>(n).to_string();
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
