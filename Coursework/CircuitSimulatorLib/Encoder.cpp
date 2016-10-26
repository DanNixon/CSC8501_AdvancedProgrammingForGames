/** @file */

#include "Encoder.h"

#include <map>

namespace CircuitSimulator
{
/**
 * @brief Creates a new encoder.
 *
 * CReates a Circuit with a single bit on the input bus and two bits on the
 * output bus.
 */
Encoder::Encoder()
    : Circuit({"bit_0"}, {"bit_0", "bit_1"})
{
}

Encoder::~Encoder()
{
}

/**
 * @copydoc Circuit::addComponent
 */
void Encoder::addComponent(Component_ptr component)
{
  Circuit::addComponent(component);

  RegisterArray_ptr ra = std::dynamic_pointer_cast<RegisterArray>(component);
  if (ra != nullptr)
    m_registers.push_back(ra);
}

/**
 * @brief Checks to ensure that all components in this Circuit are used.
 * @return True if all components are used
 * @see Component::hasLogicalConnection()
 */
bool Encoder::validateComponentUse()
{
  for (auto it = m_components.cbegin(); it != m_components.cend(); ++it)
  {
    if (!(*it)->hasLogicalConnection())
      return false;
  }

  return true;
}

/**
 * @brief Shifts all registers in the encoder.
 * @param direction Direction to shift in (-1 for left, 1 for right)
 */
void Encoder::advanceRegisters(int8_t direction)
{
  for (auto it = m_registers.begin(); it != m_registers.end(); ++it)
  {
    switch (direction)
    {
    case -1:
      (*it)->shiftLeft();
      break;
    case 1:
      (*it)->shiftRight();
      break;
    default:
      throw std::runtime_error("Invalid shift direction");
    }
  }
}

/**
 * @brief Resets all registers to all zeros.
 */
void Encoder::resetRegisters()
{
  for (auto it = m_registers.begin(); it != m_registers.end(); ++it)
    (*it)->reset();
}

/**
 * @brief Encodes a string of bits.
 * @param in Input data
 * @param out Output data
 */
void Encoder::encode(const BitStream &in, BitStream &out)
{
  for (auto it = in.cbegin(); it != in.cend(); ++it)
  {
    setInput("bit_0", *it);
    out.push_back(getOutput("bit_0"));
    out.push_back(getOutput("bit_1"));
    advanceRegisters(-1);
  }
}
}
