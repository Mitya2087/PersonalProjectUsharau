#include "../backend/ExpressionEvaluator.h"
#include "../cli/CalculatorApp.h"
#include "../utils/ArgumentParser.h"
#include <iostream>

int main(int argc, char *argv[]) {
  // Parse command-line arguments
  ArgumentParser args;
  if (!args.parse(argc, argv)) {
    return 1;
  }

  // Handle --help
  if (args.shouldShowHelp()) {
    ArgumentParser::showHelp();
    return 0;
  }

  // Handle --calc (direct calculation mode)
  if (args.shouldCalculateDirect()) {
    std::string expr = args.getExpression();
    try {
      double result = ExpressionEvaluator::evaluate(expr);
      std::cout << expr << " = " << result << std::endl;
      return 0;
    } catch (const std::exception &e) {
      std::cerr << "Error: " << e.what() << std::endl;
      return 1;
    }
  }

  // Interactive mode
  CalculatorApp app;

  // Load history if requested
  if (args.shouldLoadHistory()) {
    try {
      // We'll add this method to CalculatorApp
      std::cout << "Loading history from: " << args.getHistoryFile()
                << std::endl;
      // app.loadHistory(args.getHistoryFile());
    } catch (const std::exception &e) {
      std::cerr << "Warning: Could not load history: " << e.what() << std::endl;
    }
  }

  app.run();
  return 0;
}
