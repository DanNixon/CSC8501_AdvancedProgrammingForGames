/** @file */

#include "Encoder.h"

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
void Encoder::addComponent(Component *component)
{
  Circuit::addComponent(component);

  RegisterArray *ra = dynamic_cast<RegisterArray *>(component);
  if (ra != nullptr)
    m_registers.push_back(ra);
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
}
