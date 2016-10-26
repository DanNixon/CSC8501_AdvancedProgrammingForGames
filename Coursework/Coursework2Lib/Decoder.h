/** @file */

#pragma once

#include <map>
#include <string>
#include <vector>

#include "CircuitSimulatorLib/BitStream.h"

namespace Coursework2
{
class Decoder
{
public:
  static const std::vector<bool> OBSERVATION_SPACE;
  static const std::vector<std::string> STATE_SPACE;

public:
  Decoder();
  virtual ~Decoder();

  void decode(const CircuitSimulator::BitStream &observations);
  void decode(const std::vector<std::string> &observations);
};
}