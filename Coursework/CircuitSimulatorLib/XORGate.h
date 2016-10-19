/** @file */

#pragma once

#include "Component.h"

namespace CircuitSimulator
{
/**
 * @class XORGate
 * @author Dan Nixon
 * @brief Standard XOR gate.
 */
class XORGate : public Component
{
public:
  XORGate(const std::string &id);
  virtual ~XORGate();

  virtual void operate();
};
}
