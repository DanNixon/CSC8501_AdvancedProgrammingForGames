/** @file */

#pragma once

#include <string>
#include <vector>

namespace CircuitSimulator
{
/**
 * @brief Helper type to hold string definition of a wire between two Pin.
 */
typedef std::pair<std::string, std::string> WireDef;

/**
 * @brief List of wire definitions.
 */
typedef std::vector<WireDef> WireDefList;

std::ostream &operator<<(std::ostream &stream, const WireDef &o);
std::istream &operator>>(std::istream &stream, WireDef &o);
}
