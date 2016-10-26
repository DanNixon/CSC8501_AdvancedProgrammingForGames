/** @file */

#include "Decoder.h"

#include <sstream>

namespace Coursework2
{
Decoder::Decoder(const TransitionMatrix &transition, const EmissionMatrix &emission)
    : m_transition(transition)
    , m_emission(emission)
{
}

Decoder::~Decoder()
{
}

void Decoder::decode(const CircuitSimulator::BitStream &observations)
{
  std::vector<std::string> strObs;
  strObs.reserve(observations.size() / 2);

  for (auto it = observations.cbegin(); it != observations.cend();)
  {
    std::stringstream o;
    o << *(it++) << *(it++);
    strObs.push_back(o.str());
  }

  decode(strObs);
}

void Decoder::decode(const std::vector<std::string> &observations)
{
  // TODO
}
}