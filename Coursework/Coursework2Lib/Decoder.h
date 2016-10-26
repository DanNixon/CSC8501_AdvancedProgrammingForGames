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
  typedef std::map<std::string, double> TransitionMatrix;
  typedef std::map<std::string, double> EmissionMatrix;

public:
  static const std::vector<bool> OBSERVATION_SPACE;
  static const std::vector<std::string> STATE_SPACE;

public:
  Decoder(const TransitionMatrix &transition, const EmissionMatrix &emission);
  virtual ~Decoder();

  void decode(const CircuitSimulator::BitStream &observations);
  void decode(const std::vector<std::string> &observations);

private:
  const TransitionMatrix m_transition;
  const EmissionMatrix &m_emission;
};
}