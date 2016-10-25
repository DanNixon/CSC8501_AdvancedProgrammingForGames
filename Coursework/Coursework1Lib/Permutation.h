/** @file */

#pragma once

#include <vector>

#include "CircuitSimulatorLib/Circuit_fwd.h"
#include "CircuitSimulatorLib/Wire.h"

namespace Coursework1
{
class Permutation
{
public:
  Permutation(const CircuitSimulator::WireDefList &wires);
  virtual ~Permutation();

  inline size_t numWires() const
  {
    return m_wires.size();
  }

  void apply(CircuitSimulator::Circuit_ptr c);

  friend std::ostream &operator<<(std::ostream &stream, const Permutation &o);

private:
  const CircuitSimulator::WireDefList m_wires;
};
}