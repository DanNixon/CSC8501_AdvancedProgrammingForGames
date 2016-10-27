/** @file */

#pragma once

#include <vector>

#include "CircuitSimulatorLib/Circuit_fwd.h"
#include "CircuitSimulatorLib/Wire.h"

namespace Coursework
{
/**
 * @class Permutation
 * @author Dan Nixon
 * @brief Class holding details of an encoder permutation.
 */
class Permutation
{
public:
  Permutation(const CircuitSimulator::WireDefList &wires);
  Permutation(const Permutation &other);
  virtual ~Permutation();

  /**
   * @brief Gets the number of wires in this permutation.
   * @return Wire count
   */
  inline size_t numWires() const
  {
    return m_wires.size();
  }

  /**
   * @brief Gets a wire from this permutation.
   * @param idx Wire index
   * @return Wire
   */
  inline CircuitSimulator::WireDef wire(size_t idx) const
  {
    return m_wires[idx];
  }

  void apply(CircuitSimulator::Circuit_ptr c);

  friend std::ostream &operator<<(std::ostream &stream, const Permutation &o);

private:
  const CircuitSimulator::WireDefList m_wires; //!< Wires used to make up this permutation
};
}
