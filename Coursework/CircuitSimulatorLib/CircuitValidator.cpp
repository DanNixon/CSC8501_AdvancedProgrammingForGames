/** @file */

#include "CircuitValidator.h"
#include "Circuit.h"

namespace CircuitSimulator
{
bool CircuitValidator::Validate(const Circuit *c)
{
  Component_const_ptr root = c->component(Circuit::OUTPUT_BUS_NAME);

  // TODO
  return false;
}
}