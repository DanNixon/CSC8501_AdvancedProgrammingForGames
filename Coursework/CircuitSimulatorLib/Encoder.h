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

  virtual void addComponent(Component_ptr component);

  void advanceRegisters(int8_t direction);

  void encode(const std::vector<bool> &in, std::vector<bool> &out);

private:
  std::vector<RegisterArray_ptr> m_registers; //!< Components that are registers
};

typedef std::shared_ptr<Encoder> Encoder_ptr;
typedef std::shared_ptr<const Encoder> Encoder_const_ptr;
}
