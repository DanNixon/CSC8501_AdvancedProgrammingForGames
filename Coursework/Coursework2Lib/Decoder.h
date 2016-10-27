/** @file */

#pragma once

#include <string>
#include <vector>

#include "CircuitSimulatorLib/BitStream.h"

#include "Trellis.h"

namespace Coursework2
{
/**
 * @brief Contains information used for building path trees in viterbi decoding.
 */
struct ViterbiNode
{
  ViterbiNode()
      : pathMetric(0.0)
      , parent(nullptr)
      , bit(false)
  {
  }

  double pathMetric; //!< Best path metric at this node
  ViterbiNode *parent; //!< Parent node that gives the best path matric
  bool bit; //!< The bit decoded by following the path from the parent node
};

/**
 * @class Decoder
 * @author Dan Nixon
 * @brief Performs decoding of convolutional codes.
 */
class Decoder
{
public:
  static const size_t HammingDist(const std::string &a, const std::string &b);

public:
  Decoder(const Trellis &trellis);
  virtual ~Decoder();

  double decode(const CircuitSimulator::BitStream &observations,
              CircuitSimulator::BitStream &results);
  double decode(const std::vector<std::string> &observations, CircuitSimulator::BitStream &results);

private:
  const Trellis m_trellis; //!< Trellis used for decoding
};
}
