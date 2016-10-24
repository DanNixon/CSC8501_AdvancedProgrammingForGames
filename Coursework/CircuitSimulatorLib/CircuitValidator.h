/** @file */

#pragma once

#include <vector>

#include "Circuit_fwd.h"
#include "Component_fwd.h"
#include "Pin_fwd.h"

namespace CircuitSimulator
{
/**
 * @class CircuitValidator
 * @author Dan Nixon
 * @brief Contains functions for validating the connections in a Circuit.
 */
class CircuitValidator
{
public:
  /**
   * @brief Type used to keep the stack in the depth first traversal done during
   *        validation.
   */
  typedef std::vector<const Pin *> PinStack;

public:
  static bool Validate(const Circuit *c);

private:
  static bool ValidateComponent(Component_const_ptr component, PinStack &stack);
  static bool ValidatePin(Pin_const_ptr pin, PinStack &stack, bool biDirPin = false);
};
}
