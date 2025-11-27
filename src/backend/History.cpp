#include "History.h"
#include <fstream>
#include <iostream>

void History::addEntry(const std::string &operation, double result) {
  if (currentIndex_ < (int)entries_.size() - 1) {
    entries_.erase(entries_.begin() + currentIndex_ + 1, entries_.end());
  }

  entries_.emplace_back(operation, result);
  currentIndex_ = entries_.size() - 1;
}

void History::display() const {
  if (entries_.empty()) {
    std::cout << "History is empty.\n";
    return;
  }

  std::cout << "\n--- History ---\n";
  for (size_t i = 0; i < entries_.size(); ++i) {
    std::cout << i + 1 << ". " << entries_[i].operation << " = "
              << entries_[i].result;
    if ((int)i == currentIndex_)
      std::cout << " [CURRENT]";
    std::cout << std::endl;
  }
}

bool History::undo() {
  if (currentIndex_ > 0) {
    --currentIndex_;
    std::cout << "Undone. Current: " << entries_[currentIndex_].operation
              << " = " << entries_[currentIndex_].result << std::endl;
    return true;
  }
  std::cout << "Nothing to undo.\n";
  return false;
}

bool History::redo() {
  if (currentIndex_ < (int)entries_.size() - 1) {
    ++currentIndex_;
    std::cout << "Redone. Current: " << entries_[currentIndex_].operation
              << " = " << entries_[currentIndex_].result << std::endl;
    return true;
  }
  std::cout << "Nothing to redo.\n";
  return false;
}

void History::save(const std::string &filename) const {
  std::ofstream file(filename);
  if (!file) {
    std::cout << "Failed to open file for writing.\n";
    return;
  }

  for (const auto &entry : entries_) {
    file << entry.operation << "|" << entry.result << "\n";
  }

  std::cout << "History saved to " << filename << std::endl;
}

void History::load(const std::string &filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cout << "Failed to open file for reading.\n";
    return;
  }

  entries_.clear();
  std::string line;
  while (std::getline(file, line)) {
    size_t pos = line.find('|');
    if (pos != std::string::npos) {
      std::string op = line.substr(0, pos);
      double res = std::stod(line.substr(pos + 1));
      entries_.emplace_back(op, res);
    }
  }

  currentIndex_ = entries_.empty() ? -1 : entries_.size() - 1;
  std::cout << "History loaded from " << filename << std::endl;
}

void History::clear() {
  entries_.clear();
  currentIndex_ = -1;
  std::cout << "History cleared.\n";
}
