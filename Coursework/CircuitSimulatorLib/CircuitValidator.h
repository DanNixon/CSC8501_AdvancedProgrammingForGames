/** @file */

#pragma once

#include <vector>

#include "Circuit_fwd.h"
#include "Component_fwd.h"
#include "Pin_fwd.h"

namespace CircuitSimulator
{
class CircuitValidator
{
public:
  typedef std::vector<const Pin *> PinStack;

public:
  static bool Validate(const Circuit *c);

private:
  static bool ValidateComponent(Component_const_ptr component, PinStack &stack);
  static bool ValidatePin(Pin_const_ptr pin, PinStack &stack,
                          bool comp = false);
};
}