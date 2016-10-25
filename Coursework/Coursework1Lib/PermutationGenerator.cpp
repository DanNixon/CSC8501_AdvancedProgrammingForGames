/** @file */

#include "PermutationGenerator.h"

using namespace CircuitSimulator;

#define IS_ACTIVE_BIT (mask & (size_t)0x1 << i) > 0

namespace Coursework1
{
PermutationGenerator::PermutationGenerator(const CircuitSimulator::WireDefList &wires)
    : m_wires(wires)
    , m_numPermutations((size_t)(std::pow(2, wires.size() + 1) - 1))
{
}

PermutationGenerator::~PermutationGenerator()
{
}

Permutation PermutationGenerator::permutation(size_t mask)
{
  WireDefList wires;

  for (size_t i = 0; i < m_wires.size(); i++)
  {
    if (IS_ACTIVE_BIT)
      wires.push_back(m_wires[i]);
  }

  return Permutation(wires);
}

void PermutationGenerator::printPermutation(size_t mask, std::ostream &str)
{
  for (size_t i = 0; i < m_wires.size(); i++)
  {
    if (IS_ACTIVE_BIT)
      str << m_wires[i].first << " -> " << m_wires[i].second << '\n';
  }
}
}