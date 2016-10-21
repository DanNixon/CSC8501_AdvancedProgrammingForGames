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

#if 0
bool Component::validate() const
{
  bool retVal = true;

  for (auto it = m_pins.begin(); it != m_pins.end(); ++it)
  {
    if (!(*it)->isInput())
      continue;

    std::vector<Pin *> dftStack;
    if (!(*it)->depthFirstValidation(dftStack))
    {
      retVal = false;
      break;
    }
  }

  return retVal;
}

bool Pin::depthFirstValidation(std::vector<Pin *> &stack, bool comp)
{
  // Check if this pin is in the stack, if so there is a cycle
  if (std::find(stack.begin(), stack.end(), this) != stack.end())
    return false;

  // Add this pin to the stack
  stack.push_back(this);

  bool retVal = true;

  // Check all incomming connections for an input pin
  if (isInput())
  {
    for (auto it = m_inboundConnections.begin();
         it != m_inboundConnections.end(); ++it)
    {
      if (!(*it)->depthFirstValidation(stack))
      {
        retVal = false;
        break;
      }
    }
  }

  // Check all input pins of component if this is an output pin
  if (isOutput() && retVal && !comp)
  {
    for (auto it = m_parentComponent->m_pins.begin();
         it != m_parentComponent->m_pins.end(); ++it)
    {
      if (!(*it)->isInput() || (*it).get() == this)
        continue;

      if (!(*it)->depthFirstValidation(stack, true))
      {
        retVal = false;
        break;
      }
    }
  }

  // Pop this node from the stack
  stack.pop_back();

  return retVal;
}
#endif

}
