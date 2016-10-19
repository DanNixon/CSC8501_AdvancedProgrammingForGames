/** @file */

#pragma once

#include "Circuit.h"

#include <vector>

#include "RegisterArray.h"

namespace CircuitSimulator
{
/**
 * @class Encoder
 * @author Dan Nixon
 * @brief Specialisation of a Circuit for a convolutional encoder.
 */
class Encoder : public Circuit
{
public:
  Encoder();
  virtual ~Encoder();

  virtual void addComponent(Component *component);

  void advanceRegisters(int8_t direction);

private:
  std::vector<RegisterArray *> m_registers; //!< Components that are registers
};
}
