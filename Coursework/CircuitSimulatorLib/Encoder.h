/** @file */

#pragma once

#include "Circuit.h"

#include <vector>

#include "BitStream.h"
#include "RegisterArray.h"
#include "Trellis.h"

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

  bool validateComponentUse();

  void advanceRegisters(int8_t direction);
  void resetRegisters();
  void encode(const BitStream &in, BitStream &out);

  Trellis generateTrellis();

private:
  std::vector<RegisterArray_ptr> m_registers; //!< Components that are registers
};

/**
 * @brief Shared pointer to an Encoder.
 */
typedef std::shared_ptr<Encoder> Encoder_ptr;

/**
 * @brief Shared pointer to a const Encoder.
 */
typedef std::shared_ptr<const Encoder> Encoder_const_ptr;
}
