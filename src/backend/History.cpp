#include "History.h"
#include <cstdint>
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

  // Save only entries up to currentIndex_ (not undone entries)
  for (int i = 0; i <= currentIndex_ && i < (int)entries_.size(); ++i) {
    file << entries_[i].operation << "|" << entries_[i].result << "\n";
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

void History::saveBinary(const std::string &filename) const {
  std::ofstream file(filename, std::ios::binary);
  if (!file) {
    std::cout << "Failed to open file for binary writing.\n";
    return;
  }

  // Magic number and version
  const char magic[4] = {'H', 'I', 'S', 'T'};
  file.write(magic, 4);

  uint32_t version = 1;
  file.write(reinterpret_cast<const char *>(&version), sizeof(version));

  // Entry count - only save entries up to currentIndex_
  uint32_t count = (currentIndex_ >= 0) ? (currentIndex_ + 1) : 0;
  file.write(reinterpret_cast<const char *>(&count), sizeof(count));

  // Write each entry (only up to currentIndex_)
  for (int i = 0; i <= currentIndex_ && i < (int)entries_.size(); ++i) {
    const auto &entry = entries_[i];
    // Operation string length and data
    uint32_t opLength = entry.operation.length();
    file.write(reinterpret_cast<const char *>(&opLength), sizeof(opLength));
    file.write(entry.operation.c_str(), opLength);

    // Result (double)
    file.write(reinterpret_cast<const char *>(&entry.result),
               sizeof(entry.result));
  }

  // Current index
  int32_t currentIdx = currentIndex_;
  file.write(reinterpret_cast<const char *>(&currentIdx), sizeof(currentIdx));

  std::cout << "History saved to binary file " << filename << std::endl;
}

void History::loadBinary(const std::string &filename) {
  std::ifstream file(filename, std::ios::binary);
  if (!file) {
    std::cout << "Failed to open binary file for reading.\n";
    return;
  }

  // Read and verify magic number
  char magic[4];
  file.read(magic, 4);
  if (magic[0] != 'H' || magic[1] != 'I' || magic[2] != 'S' ||
      magic[3] != 'T') {
    std::cout << "Invalid binary history file format.\n";
    return;
  }

  // Read version
  uint32_t version;
  file.read(reinterpret_cast<char *>(&version), sizeof(version));

  // Read entry count
  uint32_t count;
  file.read(reinterpret_cast<char *>(&count), sizeof(count));

  entries_.clear();

  // Read each entry
  for (uint32_t i = 0; i < count; ++i) {
    // Read operation string
    uint32_t opLength;
    file.read(reinterpret_cast<char *>(&opLength), sizeof(opLength));

    std::string operation(opLength, '\0');
    file.read(&operation[0], opLength);

    // Read result
    double result;
    file.read(reinterpret_cast<char *>(&result), sizeof(result));

    entries_.emplace_back(operation, result);
  }

  // Read current index
  int32_t currentIdx;
  file.read(reinterpret_cast<char *>(&currentIdx), sizeof(currentIdx));
  currentIndex_ = currentIdx;

  std::cout << "History loaded from binary file " << filename << std::endl;
}

void History::clear() {
  entries_.clear();
  currentIndex_ = -1;
  std::cout << "History cleared.\n";
}
