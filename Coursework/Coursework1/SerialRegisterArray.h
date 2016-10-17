#pragma once

#include "Component.h"

#include <bitset>

namespace CircuitSimulator
{
class SerialRegisterArray : public Component
{
public:
  SerialRegisterArray(const std::string &id, size_t numElements)
      : Component(id, "Register Array", {}, {})
  {
    for (size_t i = 0; i < numElements; i++)
      m_pins.push_back(new Pin(("bit_" + std::to_string(i)),
                               PIN_FLAG_OUTPUT | PIN_FLAG_INPUT));
  }

  virtual ~SerialRegisterArray()
  {
  }

  virtual void operate()
  {
    // Nothing to do here
  }

  void shiftLeft()
  {
    // TODO
  }

  void shiftRight()
  {
    // TODO
  }
};
}