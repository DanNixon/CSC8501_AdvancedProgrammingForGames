#include "Encoder.h"

namespace CircuitSimulator
{
Encoder::Encoder()
    : Circuit({"bit_0"}, {"bit_0", "bit_1"})
{
}

Encoder::~Encoder()
{
}

void Encoder::addComponent(Component *component)
{
  Circuit::addComponent(component);

  RegisterArray *ra = dynamic_cast<RegisterArray *>(component);
  if (ra != nullptr)
    m_registers.push_back(ra);
}

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