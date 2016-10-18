#pragma once

#include "Circuit.h"

#include <vector>

#include "SerialRegisterArray.h"

namespace CircuitSimulator
{
class Encoder : public Circuit
{
public:
  Encoder();
  virtual ~Encoder();

  virtual void addComponent(Component *component);

  void advanceRegisters(int8_t direction);

private:
  std::vector<SerialRegisterArray *> m_registers;
};
}