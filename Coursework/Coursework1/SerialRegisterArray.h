#pragma once

#include "Component.h"

#include <bitset>

template <size_t N> class SerialRegisterArray : public Component
{
public:
  SerialRegisterArray()
  {
  }

  virtual ~SerialRegisterArray()
  {
  }

  virtual void operate()
  {
    // Nothing to do here
  }

private:
  std::bitset<N + 1>
      m_registers; // Number of registers required plus one space for the input
};
