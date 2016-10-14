#pragma once

#include "Device.h"

#include <bitset>

template <size_t N>
class SerialRegisterArray : public Device<bool>
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
  std::bitset<N> m_registers;
};