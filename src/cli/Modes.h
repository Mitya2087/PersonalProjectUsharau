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

#endif
