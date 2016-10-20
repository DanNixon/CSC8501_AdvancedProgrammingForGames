/** @file */

#include "Pin.h"

#include <algorithm>

#include "Component.h"

namespace CircuitSimulator
{
/**
 * @brief Create a new pin.
 * @param parent Pointer to the parent component
 * @param id String ID of the pin
 * @param flags IO flags
 */
Pin::Pin(Component *parent, const std::string &id, uint8_t flags)
    : m_parentComponent(parent)
    , m_id(id)
    , m_flags(flags)
    , m_state(false)
    , m_onChange([]() {})
{
}

Pin::~Pin()
{
}

/**
 * @brief Checks if this pin is an input.
 * @return True if PIN_FLAG_INPUT is set
 */
bool Pin::isInput() const
{
  return (m_flags & PIN_FLAG_INPUT) > 0;
}

/**
 * @brief Checks if this pin is an output.
 * @return True if PIN_FLAG_OUTPUT is set
 */
bool Pin::isOutput() const
{
  return (m_flags & PIN_FLAG_OUTPUT) > 0;
}

/**
 * @brief Wires this pin to another pin.
 * @param other Other pin to wire to
 */
void Pin::wireTo(Pin *other)
{
  if (!((PIN_FLAG_INPUT | PIN_FLAG_OUTPUT) & (m_flags | other->m_flags)))
    throw std::runtime_error("Wire has no directionality");

  m_outboundConnections.push_back(other);
  other->m_inboundConnections.push_back(this);
}

/**
 * @brief Sets the function to be called when the value of this pin changes.
 * @param func Function
 */
void Pin::setOnChange(std::function<void(void)> func)
{
  m_onChange = func;
}

/**
 * @brief Sets the state of this pin.
 * @param state New state
 */
void Pin::setState(bool state)
{
  m_state = state;

  /* Set state of outbound connections */
  for (auto it = m_outboundConnections.begin();
       it != m_outboundConnections.end(); ++it)
    (*it)->setState(m_state);

  m_onChange();
}

/**
 * @brief Performs a depth first traversal to validate that there are no cycles in the inbound connections of this pin.
 * @param stack Reference to the stack of pins traversed
 * @return True if stack contained no duplicates
 */
bool Pin::depthFirstValidation(std::vector<Pin*> & stack, bool comp)
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
    for (auto it = m_inboundConnections.begin(); it != m_inboundConnections.end(); ++it)
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
    for (auto it = m_parentComponent->m_pins.begin(); it != m_parentComponent->m_pins.end(); ++it)
    {
      if (!(*it)->isInput() || *it == this)
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
}
