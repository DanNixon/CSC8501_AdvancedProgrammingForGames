/** @file */

#include "Decoder.h"

#include <sstream>
#include <algorithm>

using namespace CircuitSimulator;

namespace Coursework2
{
/**
 * @brief Measures the hamming distance between two strings.
 * @param a First string
 * @param b Second string
 * @return Hamming distance
 */
const size_t Decoder::HammingDist(const std::string & a, const std::string & b)
{
  size_t dist = 0;

  auto aIt = a.cbegin();
  auto bIt = b.cbegin();

  while (aIt != a.cend() && bIt != b.cend())
  {
    if (*(aIt++) != *(bIt++))
      dist++;
  }

  return dist;
}

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
  ViterbiNode * states[4];
  ViterbiNode * statesNext[4];

  // Initial states
  for (size_t i = 0; i < 4; i++)
    statesNext[i] = new ViterbiNode();
  
  // Process trellis and build paths
  for (auto it = observations.begin(); it != observations.end(); ++it)
  {
    // Move current trellis frame
    for (size_t i = 0; i < 4; i++)
    {
      states[i] = statesNext[i];
      statesNext[i] = new ViterbiNode();
    }

    // Process states in current trellis frame
    for (size_t i = 0; i < 4; i++)
    {
      // Compute new path matrics
      // TODO

      // Select best path
      // TODO
    }
  }

  // Find best path (lowest path metric)
  ViterbiNode *best = states[0];
  for (size_t i = 1; i < 4; i++)
    if (states[i]->pathMetric < best->pathMetric)
      best = states[i];

  // Backtrack
  while (best->parent != nullptr)
  {
    results.push_back(best->bit);
    best = best->parent;
  }

  // Backtracking gives reverse path
  std::reverse(results.begin(), results.end());
}
}
