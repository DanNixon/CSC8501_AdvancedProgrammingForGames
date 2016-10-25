/** @file */

#include "Wire.h"

namespace CircuitSimulator
{
std::ostream &operator<<(std::ostream &stream, const WireDef &o)
{
  stream << o.first << " -> " << o.second;
  return stream;
}

std::istream &operator>>(std::istream &stream, WireDef &o)
{
  std::getline(stream, o.first, '>');
  stream >> o.second;
  return stream;
}
}