#ifndef DATEMODE_H
#define DATEMODE_H

#include <ctime>
#include <string>

/**
 * @brief Date calculation mode for working with dates
 *
 * Supports date arithmetic, difference calculation, and formatting
 */
class DateMode {
public:
  /**
   * @brief Execute date calculation mode
   */
  void execute();

private:
  /**
   * @brief Parse date string in format DD/MM/YYYY or DD-MM-YYYY
   */
  std::tm parseDate(const std::string &dateStr);

  /**
   * @brief Calculate difference between two dates in days
   */
  int dateDifference(const std::tm &date1, const std::tm &date2);

  /**
   * @brief Add days to a date
   */
  std::tm addDays(const std::tm &date, int days);

  /**
   * @brief Format date as string
   */
  std::string formatDate(const std::tm &date);

  /**
   * @brief Display date mode menu
   */
  void displayMenu();
};

#endif // DATEMODE_H
