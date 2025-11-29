#ifndef MODES_H
#define MODES_H

#include <string>
#include <vector>

class Mode {
public:
  virtual ~Mode() = default;
  virtual void run() = 0;
  virtual std::string getName() const = 0;
};

class StandardMode : public Mode {
public:
  void run() override;
  std::string getName() const override { return "Standard Mode"; }
};

class ScientificMode : public Mode {
public:
  void run() override;
  std::string getName() const override { return "Scientific Mode"; }
};

class ProgrammerMode : public Mode {
public:
  void run() override;
  std::string getName() const override { return "Programmer Mode"; }

private:
  std::string toBinary(long long n);
  std::string toHex(long long n);
  long long fromBinary(std::string s);
  long long fromHex(std::string s);
};

#endif
