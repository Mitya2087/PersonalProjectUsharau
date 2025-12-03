#include "DateMode.h"
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>

void DateMode::execute() {
  std::cout << "\n=== Date Calculation Mode ===\n";
  std::cout << "Format: DD/MM/YYYY or DD-MM-YYYY\n\n";

  while (true) {
    displayMenu();

    int choice;
    std::cin >> choice;
    std::cin.ignore();

    if (choice == 0) {
      break;
    }

    try {
      if (choice == 1) {
        std::cout << "Enter first date: ";
        std::string date1Str;
        std::getline(std::cin, date1Str);

        std::cout << "Enter second date: ";
        std::string date2Str;
        std::getline(std::cin, date2Str);

        std::tm date1 = parseDate(date1Str);
        std::tm date2 = parseDate(date2Str);

        int diff = dateDifference(date1, date2);
        std::cout << "Difference: " << std::abs(diff) << " days\n";
      } else if (choice == 2) {
        std::cout << "Enter date: ";
        std::string dateStr;
        std::getline(std::cin, dateStr);

        std::cout << "Enter number of days to add (negative to subtract): ";
        int days;
        std::cin >> days;
        std::cin.ignore();

        std::tm date = parseDate(dateStr);
        std::tm result = addDays(date, days);

        std::cout << "Result: " << formatDate(result) << "\n";
      } else if (choice == 3) {
        std::cout << "Enter target date: ";
        std::string dateStr;
        std::getline(std::cin, dateStr);

        std::tm targetDate = parseDate(dateStr);
        std::time_t now = std::time(nullptr);
        std::tm *today = std::localtime(&now);

        int diff = dateDifference(*today, targetDate);

        if (diff > 0) {
          std::cout << "Days until " << formatDate(targetDate) << ": " << diff
                    << " days\n";
        } else if (diff < 0) {
          std::cout << "Date was " << abs(diff) << " days ago\n";
        } else {
          std::cout << "That's today!\n";
        }
      } else {
        std::cout << "Invalid choice.\n";
      }
    } catch (const std::exception &e) {
      std::cout << "Error: " << e.what() << "\n";
    }

    std::cout << "\n";
  }
}

void DateMode::displayMenu() {
  std::cout << "1. Calculate difference between two dates\n";
  std::cout << "2. Add/subtract days from a date\n";
  std::cout << "3. Days until a date\n";
  std::cout << "0. Back to main menu\n";
  std::cout << "> ";
}

std::tm DateMode::parseDate(const std::string &dateStr) {
  std::tm date = {};
  int day, month, year;
  char sep;

  std::istringstream iss(dateStr);
  if (!(iss >> day >> sep >> month >> sep >> year)) {
    throw std::runtime_error("Invalid date format. Use DD/MM/YYYY");
  }

  if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900) {
    throw std::runtime_error("Invalid date values");
  }

  date.tm_mday = day;
  date.tm_mon = month - 1;
  date.tm_year = year - 1900;
  date.tm_hour = 12;

  return date;
}

int DateMode::dateDifference(const std::tm &date1, const std::tm &date2) {
  std::tm d1 = date1;
  std::tm d2 = date2;

  std::time_t time1 = std::mktime(&d1);
  std::time_t time2 = std::mktime(&d2);

  double seconds = std::difftime(time2, time1);
  return static_cast<int>(seconds / (60 * 60 * 24));
}

std::tm DateMode::addDays(const std::tm &date, int days) {
  std::tm result = date;
  std::time_t time = std::mktime(&result);
  time += days * 24 * 60 * 60;

  std::tm *newDate = std::localtime(&time);
  return *newDate;
}

std::string DateMode::formatDate(const std::tm &date) {
  std::ostringstream oss;
  oss << std::setfill('0') << std::setw(2) << date.tm_mday << "/"
      << std::setw(2) << (date.tm_mon + 1) << "/" << (date.tm_year + 1900);
  return oss.str();
}
