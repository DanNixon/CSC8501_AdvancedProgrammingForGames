#include "Pin.h"

#include <algorithm>

namespace CircuitSimulator
{
Pin::Pin(const std::string &id, uint8_t flags)
    : m_id(id)
    , m_flags(flags)
    , m_state(false)
    , m_onChange([]() {})
{
}

Pin::~Pin()
{
}

bool Pin::isInput() const
{
  return (m_flags & PIN_FLAG_INPUT) > 0;
}

bool Pin::isOutput() const
{
  return (m_flags & PIN_FLAG_OUTPUT) > 0;
}

void Pin::wireTo(Pin *other)
{
  if (!((PIN_FLAG_INPUT | PIN_FLAG_OUTPUT) & (m_flags | other->m_flags)))
    throw std::runtime_error("Wire has no directionality");

  m_outboundConnections.push_back(other);
}

void Pin::setOnChange(std::function<void(void)> func)
{
  m_onChange = func;
}

void Pin::setState(bool state)
{
  m_state = state;

  // Set state of outbound connections
  for (auto it = m_outboundConnections.begin();
       it != m_outboundConnections.end(); ++it)
    (*it)->setState(m_state);

  m_onChange();
}
}