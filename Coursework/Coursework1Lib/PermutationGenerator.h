/** @file */

#pragma once

#include "CircuitSimulatorLib/Wire.h"

#include "Permutation.h"

namespace Coursework1
{
class PermutationGenerator
{
public:
  PermutationGenerator(const CircuitSimulator::WireDefList &wires);
  virtual ~PermutationGenerator();

  inline size_t numPermutations() const
  {
    return m_numPermutations;
  }

  Permutation permutation(size_t mask);
  void printPermutation(size_t mask, std::ostream &str);

private:
  const CircuitSimulator::WireDefList &m_wires;
  const size_t m_numPermutations;
};
}