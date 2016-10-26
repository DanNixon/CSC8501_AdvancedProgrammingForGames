/** @file */

#include "Decoder.h"

#include <sstream>

using namespace CircuitSimulator;

namespace Coursework2
{
/**
 * @brief Creates a new decoder with a given Trellis.
 * @param trellis Trellis to use for decoding
 */
Decoder::Decoder(const Trellis &trellis)
    : m_trellis(trellis)
{
}

Decoder::~Decoder()
{
}

void Decoder::decode(const CircuitSimulator::BitStream &observations, BitStream &results)
{
  std::vector<std::string> strObs;
  strObs.reserve(observations.size() / 2);

  for (auto it = observations.cbegin(); it != observations.cend();)
  {
    std::stringstream o;
    o << *(it++) << *(it++);
    strObs.push_back(o.str());
  }

  decode(strObs, results);
}

void Decoder::decode(const std::vector<std::string> &observations, BitStream &results)
{
  // TODO
}
}
