/** @file */

#pragma once

#include <string>
#include <vector>

namespace CircuitSimulator
{
typedef std::pair<std::string, std::string> WireDef;
typedef std::vector<WireDef> WireDefList;

std::ostream &operator<<(std::ostream &stream, const WireDef &o);
std::istream &operator>>(std::istream &stream, WireDef &o);
}