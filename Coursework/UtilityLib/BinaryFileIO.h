/** @file */

#pragma once

#include <iostream>

#include "CircuitSimulatorLib/BitStream.h"

namespace Utility
{
class BinaryFileIO
{
public:
  static size_t Read(CircuitSimulator::BitStream &bits, std::istream &in);
  static size_t Write(const CircuitSimulator::BitStream &bits, std::ostream &out);

  static size_t ReadFile(CircuitSimulator::BitStream &bits, const std::string &filename);
  static size_t WriteFile(const CircuitSimulator::BitStream &bits, const std::string &filename);
};
}