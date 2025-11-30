#ifndef HISTORY_H
#define HISTORY_H

#include <string>
#include <vector>

class History {
public:
  void addEntry(const std::string &operation, double result);
  void display() const;
  bool undo();
  bool redo();

  // Text format I/O
  void save(const std::string &filename) const;
  void load(const std::string &filename);

  // Binary format I/O
  void saveBinary(const std::string &filename) const;
  void loadBinary(const std::string &filename);

  void clear();

private:
  struct Entry {
    std::string operation;
    double result;

    Entry(const std::string &op, double res) : operation(op), result(res) {}
  };

  std::vector<Entry> entries_;
  int currentIndex_ = -1;
};

#endif
