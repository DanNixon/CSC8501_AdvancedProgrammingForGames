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

/**
 * @brief Shared pointer to an XORGate.
 */
typedef std::shared_ptr<XORGate> XORGate_ptr;

/**
 * @brief Shared pointer to a const XORGate.
 */
typedef std::shared_ptr<const XORGate> XORGate_const_ptr;
}
