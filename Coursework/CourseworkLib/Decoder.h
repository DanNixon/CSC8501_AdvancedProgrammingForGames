/** @file */

#pragma once

#include <string>
#include <vector>

#include "CircuitSimulatorLib/BitStream.h"
#include "CircuitSimulatorLib/Trellis.h"

namespace Coursework
{
/**
 * @brief Contains information used for building path trees in viterbi decoding.
 */
struct ViterbiNode
{
  ViterbiNode()
      : pathMetric(0)
      , parent(nullptr)
      , bit(false)
  {
  }

  size_t pathMetric;   //!< Best path metric at this node
  ViterbiNode *parent; //!< Parent node that gives the best path matric
  bool bit;            //!< The bit decoded by following the path from the parent node
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
  Decoder(const CircuitSimulator::Trellis &trellis);
  virtual ~Decoder();

  size_t decode(const CircuitSimulator::BitStream &observations,
                CircuitSimulator::BitStream &results);
  size_t decode(const std::vector<std::string> &observations, CircuitSimulator::BitStream &results);

private:
  const CircuitSimulator::Trellis m_trellis; //!< Trellis used for decoding
};
}
