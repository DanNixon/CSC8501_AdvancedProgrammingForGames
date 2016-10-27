/** @file */

#include "Decoder.h"

#include <algorithm>
#include <sstream>

using namespace CircuitSimulator;

namespace Coursework2
{
/**
 * @brief Measures the hamming distance between two strings.
 * @param a First string
 * @param b Second string
 * @return Hamming distance
 */
const size_t Decoder::HammingDist(const std::string &a, const std::string &b)
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

/**
 * @brief Decodes a bit stream using the trellis.
 * @param observations Bit stream received
 * @param results Reference to storage for decoded result
 * @return Best path metric
 */
double Decoder::decode(const CircuitSimulator::BitStream &observations, BitStream &results)
{
  std::vector<std::string> strObs;
  strObs.reserve(observations.size() / 2);

  for (auto it = observations.cbegin(); it != observations.cend();)
  {
    bool bits[] = {*(it++), *(it++)};
    std::stringstream o;
    o << bits[0] << bits[1];
    strObs.push_back(o.str());
  }

  return decode(strObs, results);
}

/**
 * @brief Decodes a sequence of bit pairs using the trellis.
 * @param observations Bit pairs (as vector of string) received
 * @param results Reference to storage for decoded result
 * @return Best path metric
 */
double Decoder::decode(const std::vector<std::string> &observations, BitStream &results)
{
  ViterbiNode **states = new ViterbiNode *[m_trellis.numStates()];
  ViterbiNode **statesNext = new ViterbiNode *[m_trellis.numStates()];

  // Initial states
  for (size_t i = 0; i < m_trellis.numStates(); i++)
    statesNext[i] = new ViterbiNode();

  // Process trellis and build paths
  for (auto obsIt = observations.begin(); obsIt != observations.end(); ++obsIt)
  {
    // Move current trellis frame
    for (size_t i = 0; i < m_trellis.numStates(); i++)
    {
      states[i] = statesNext[i];
      statesNext[i] = new ViterbiNode();
    }

    // Process states in current trellis frame
    for (size_t i = 0; i < m_trellis.numStates(); i++)
    {
      // Get mappings
      std::vector<TrellisMapping> mappings;
      m_trellis.getMappingsForDestinationState(mappings, i);

      // Compute new path metrics and find best branch
      TrellisMapping bestMapping;
      bestMapping.tempCost = std::numeric_limits<double>::max();

      // For each mapping to this state in th trellis
      for (size_t j = 0; j < mappings.size(); j++)
      {
        mappings[j].tempCost =
            states[mappings[j].srcState]->pathMetric + HammingDist(mappings[j].code, *obsIt);

        // Check if this is the new lowest cost
        if (mappings[j].tempCost < bestMapping.tempCost)
          bestMapping = mappings[j];
      }

      // Add best branch to tree
      statesNext[i]->bit = bestMapping.bit;
      statesNext[i]->pathMetric = bestMapping.tempCost;
      statesNext[i]->parent = states[bestMapping.srcState];
    }
  }

  // Find best path (lowest path metric)
  ViterbiNode *best = statesNext[0];
  double bestPathMetric = best->pathMetric;
  for (size_t i = 1; i < 4; i++)
    if (statesNext[i]->pathMetric < best->pathMetric)
      best = statesNext[i];

  // Backtrack
  do
  {
    results.push_back(best->bit);
    best = best->parent;
  } while (best->parent != nullptr);

  // Backtracking gives reverse path
  std::reverse(results.begin(), results.end());

  // Free memory
  delete[] states;
  delete[] statesNext;
  // TODO: nodes

  return bestPathMetric;
}
}
