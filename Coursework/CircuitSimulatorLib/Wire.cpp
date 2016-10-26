/** @file */

#include "Wire.h"

namespace CircuitSimulator
{
/**
 * @brief Output a wire definition to a stream as a friendly formatted string.
 * @param stream Reference to output stream
 * @param o Wire definition to output
 * @return Reference to output stream
 */
std::ostream &operator<<(std::ostream &stream, const WireDef &o)
{
  stream << o.first << " -> " << o.second;
  return stream;
}

/**
 * @brief Parses a wire definition from a stream.
 * @param stream Reference to input stream
 * @param o Wire definition to populate
 * @return Reference to input stream
 *
 * Input is in format "source>destination".
 */
std::istream &operator>>(std::istream &stream, WireDef &o)
{
  std::getline(stream, o.first, '>');
  stream >> o.second;
  return stream;
}
}
