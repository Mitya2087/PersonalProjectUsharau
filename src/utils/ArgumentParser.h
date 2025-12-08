#ifndef ARGUMENTPARSER_H
#define ARGUMENTPARSER_H

#include <map>
#include <string>
#include <vector>

/**
 * @brief Command-line argument parser
 *
 * Parses and manages command-line arguments for the calculator.
 * Supports options like --help, --calc, --load-history, --log-level, etc.
 */
class ArgumentParser {
public:
  /**
   * @brief Parse command-line arguments
   * @param argc Argument count
   * @param argv Argument values
   * @return true if parsing successful, false otherwise
   */
  bool parse(int argc, char *argv[]);

  /**
   * @brief Check if help was requested
   * @return true if --help or -h flag present
   */
  bool shouldShowHelp() const;

  /**
   * @brief Check if direct calculation mode requested
   * @return true if --calc option present
   */
  bool shouldCalculateDirect() const;

  /**
   * @brief Get expression for direct calculation
   * @return Expression string from --calc option
   */
  std::string getExpression() const;

  /**
   * @brief Check if history file should be loaded
   * @return true if --load-history option present
   */
  bool shouldLoadHistory() const;

  /**
   * @brief Get history file path
   * @return File path from --load-history option
   */
  std::string getHistoryFile() const;

  /**
   * @brief Get logging level
   * @return Log level (DEBUG, INFO, WARNING, ERROR) or empty if not set
   */
  std::string getLogLevel() const;

  /**
   * @brief Get log file path
   * @return Log file path or empty if not set
   */
  std::string getLogFile() const;

  /**
   * @brief Get calculator mode
   * @return Mode name (standard, scientific, programmer) or empty
   */
  std::string getMode() const;

  /**
   * @brief Display help message
   */
  static void showHelp();

private:
  std::map<std::string, std::string> options_;
  std::vector<std::string> positionalArgs_;

  bool hasOption(const std::string &key) const;
  std::string getOption(const std::string &key,
                        const std::string &defaultValue = "") const;
};

#endif // ARGUMENTPARSER_H
