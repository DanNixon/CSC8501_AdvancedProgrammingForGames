/** @file */

#pragma once

#include <string>
#include <vector>

#include "CircuitSimulatorLib/BitStream.h"

#include "Trellis.h"

namespace Coursework2
{
/**
 * @class Decoder
 * @author Dan Nixon
 * @brief Performs decoding of convolutional codes.
 */
class Decoder
{
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
