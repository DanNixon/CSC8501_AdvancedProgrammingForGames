/** @file */

#pragma once

#include <string>
#include <vector>

#include "CircuitSimulatorLib/BitStream.h"

#include "Trellis.h"

namespace Coursework2
{
struct ViterbiNode
{
  ViterbiNode()
      : pathMetric(0.0)
      , parent(nullptr)
      , bit(false)
  {
  }

  double pathMetric;
  ViterbiNode *parent;
  bool bit;
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

  void decode(const CircuitSimulator::BitStream &observations,
              CircuitSimulator::BitStream &results);
  void decode(const std::vector<std::string> &observations, CircuitSimulator::BitStream &results);

private:
  const Trellis m_trellis; //!< Trellis used for decoding
};
}
