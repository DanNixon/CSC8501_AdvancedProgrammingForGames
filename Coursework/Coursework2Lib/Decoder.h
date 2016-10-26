/** @file */

#pragma once

#include <map>
#include <string>
#include <vector>

#include "CircuitSimulatorLib/BitStream.h"

#include "Viterbi.h"

namespace Coursework2
{
class Decoder
{
public:
  typedef Viterbi<bool, std::string> CDViterbi;

  static const CDViterbi::States STATE_SPACE;
  static const CDViterbi::Observations OBSERVATION_SPACE;
  static const CDViterbi::InitialProbability INITIAL_PROBABILITY;

public:
  Decoder();
  virtual ~Decoder();

  void decode(const CircuitSimulator::BitStream &observations, CDViterbi::States &results);
  void decode(const CDViterbi::Observations &observations, CDViterbi::States &results);
};
}