/** @file */

#include "CircuitValidator.h"

#include "Circuit.h"
#include "Component.h"
#include "Pin.h"

namespace CircuitSimulator
{
/**
 * @brief Validates the connections in a Circuit.
 * @return True if the circuit wiring is valid
 */
bool CircuitValidator::Validate(const Circuit *c)
{
  Component_const_ptr root = c->component(Circuit::OUTPUT_BUS_NAME);
  PinStack stack;
  return ValidateComponent(root, stack);
}

/**
 * @brief Recursively validates wiring of a component in a circuit.
 * @param component Const pointer to component to validate
 * @param stack Reference to the current DFT stack
 * @return True if the circuit wiring is valid for the current path
 */
bool CircuitValidator::ValidateComponent(Component_const_ptr component, PinStack &stack)
{
  bool retVal = true;

  for (auto it = component->pinsBegin(); it != component->pinsEnd(); ++it)
  {
    if (!(*it)->isInput())
      continue;

    if (!ValidatePin(*it, stack))
    {
      retVal = false;
      break;
    }
  }

  return retVal;
}

/**
 * @brief Recursively validates wiring of a pin in a circuit.
 * @param pin Const pointer to the pin to validate
 * @param stack Reference to the current DFT stack
 * @param biDirPin True if the last pin tested was an output pin
 * @return True if the circuit wiring is valid for the current path
 *
 * biDirPin must be set to true if the last pin verified was an output pin,
 * this stops the case of infinite recursion caused by validating
 * bi-directional pins on a component.
 */
bool CircuitValidator::ValidatePin(Pin_const_ptr pin, PinStack &stack, bool biDirPin)
{
  /* Check if this pin is in the stack, if so there is a cycle */
  if (std::find(stack.begin(), stack.end(), pin.get()) != stack.end())
    return false;

  /* Add this pin to the stack */
  stack.push_back(pin.get());

  bool retVal = true;

  /* Check all incomming connections for an input pin */
  if (pin->isInput())
  {
    for (auto it = pin->inboundConnectionsBegin(); it != pin->inboundConnectionsEnd(); ++it)
    {
      if (!ValidatePin(*it, stack))
      {
        retVal = false;
        break;
      }
    }
  }

  /* Check all input pins of component if this is an output pin */
  if (pin->isOutput() && retVal && !biDirPin)
  {
    for (auto it = pin->parentComponent()->pinsBegin(); it != pin->parentComponent()->pinsEnd();
         ++it)
    {
      if (!(*it)->isInput() || *it == pin)
        continue;

      if (!ValidatePin(*it, stack, true))
      {
        retVal = false;
        break;
      }
    }
  }

  /* Pop this node from the stack */
  stack.pop_back();

  return retVal;
}
}
