#include "Pin.h"

Pin::Pin(const std::string &id, uint8_t flags)
    : m_id(id)
    , m_flags(flags)
    , m_state(false)
{
}

Pin::~Pin()
{
}

bool Pin::isInput() const
{
  return m_flags & PIN_FLAG_INPUT;
}

bool Pin::isOutput() const
{
  return m_flags & PIN_FLAG_OUTPUT;
}

void Pin::setState(bool state)
{
  m_state = state;
}
