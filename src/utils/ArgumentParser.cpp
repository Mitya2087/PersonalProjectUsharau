#include "ArgumentParser.h"
#include <iostream>

bool ArgumentParser::parse(int argc, char *argv[]) {
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "--help" || arg == "-h") {
      options_["help"] = "true";
    } else if (arg == "--calc" && i + 1 < argc) {
      options_["calc"] = argv[++i];
    } else if (arg == "--load-history" && i + 1 < argc) {
      options_["load-history"] = argv[++i];
    } else if (arg == "--log-level" && i + 1 < argc) {
      std::string level = argv[++i];
      // Validate log level
      if (level == "DEBUG" || level == "INFO" || level == "WARNING" ||
          level == "ERROR") {
        options_["log-level"] = level;
      } else {
        std::cerr << "Error: Invalid log level '" << level << "'" << std::endl;
        std::cerr << "Valid levels: DEBUG, INFO, WARNING, ERROR" << std::endl;
        return false;
      }
    } else if (arg == "--log-file" && i + 1 < argc) {
      options_["log-file"] = argv[++i];
    } else if (arg == "--mode" && i + 1 < argc) {
      std::string mode = argv[++i];
      // Validate mode
      if (mode == "standard" || mode == "scientific" || mode == "programmer") {
        options_["mode"] = mode;
      } else {
        std::cerr << "Error: Invalid mode '" << mode << "'" << std::endl;
        std::cerr << "Valid modes: standard, scientific, programmer"
                  << std::endl;
        return false;
      }
    } else if (arg[0] == '-') {
      std::cerr << "Error: Unknown option '" << arg << "'" << std::endl;
      return false;
    } else {
      positionalArgs_.push_back(arg);
    }
  }

  return true;
}

bool ArgumentParser::shouldShowHelp() const { return hasOption("help"); }

bool ArgumentParser::shouldCalculateDirect() const { return hasOption("calc"); }

std::string ArgumentParser::getExpression() const { return getOption("calc"); }

bool ArgumentParser::shouldLoadHistory() const {
  return hasOption("load-history");
}

std::string ArgumentParser::getHistoryFile() const {
  return getOption("load-history");
}

std::string ArgumentParser::getLogLevel() const {
  return getOption("log-level", "INFO");
}

std::string ArgumentParser::getLogFile() const { return getOption("log-file"); }

std::string ArgumentParser::getMode() const { return getOption("mode"); }

void ArgumentParser::showHelp() {
  std::cout << "Extended Calculator - Command Line Options\n\n";
  std::cout << "Usage: calculator_cli [OPTIONS]\n\n";

  std::cout << "OPTIONS:\n";
  std::cout << "  --help, -h                Show this help message\n";
  std::cout << "  --calc EXPRESSION         Calculate expression directly\n";
  std::cout << "                            Example: --calc \"2 + 2 * 3\"\n";
  std::cout
      << "  --load-history FILE       Load calculation history from file\n";
  std::cout << "  --log-level LEVEL         Set logging level "
               "(DEBUG|INFO|WARNING|ERROR)\n";
  std::cout << "                            Default: INFO\n";
  std::cout
      << "  --log-file FILE           Write logs to file instead of console\n";
  std::cout << "  --mode MODE               Start in specific mode\n";
  std::cout
      << "                            (standard|scientific|programmer)\n\n";

  std::cout << "EXAMPLES:\n";
  std::cout << "  calculator_cli --calc \"sqrt(16)\"\n";
  std::cout << "  calculator_cli --load-history myhistory.txt\n";
  std::cout << "  calculator_cli --log-level DEBUG --log-file debug.log\n";
  std::cout << "  calculator_cli --mode scientific\n\n";
}

bool ArgumentParser::hasOption(const std::string &key) const {
  return options_.find(key) != options_.end();
}

std::string ArgumentParser::getOption(const std::string &key,
                                      const std::string &defaultValue) const {
  auto it = options_.find(key);
  if (it != options_.end()) {
    return it->second;
  }
  return defaultValue;
}
