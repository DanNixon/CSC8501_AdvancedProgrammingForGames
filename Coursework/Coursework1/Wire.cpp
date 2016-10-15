#include "Wire.h"

Wire::Wire(IComponent *source, Pin *output, IComponent *dest, Pin *input)
    : m_source(source)
    , m_destination(dest)
    , m_output(output)
    , m_input(input)
{
}

Wire::~Wire()
{
}

std::ostream &operator<<(std::ostream &stream, const Wire &o)
{
  stream << "Patch[" << (o.m_source == nullptr ? "null" : o.m_source->id())
         << (o.m_output == nullptr ? "null" : o.m_output->id()) << " -> "
         << (o.m_destination == nullptr ? "null" : o.m_destination->id())
         << (o.m_input == nullptr ? "null" : o.m_input->id()) << ']';
  return stream;
}