/** @file */

#include "PermutationGenerator.h"

using namespace CircuitSimulator;

#define IS_ACTIVE_BIT (mask & (size_t)0x1 << i) > 0

namespace Coursework1
{
PermutationGenerator::PermutationGenerator(const CircuitSimulator::WireDefList &wires,
                                           const std::vector<std::string> &validationStrings)
    : m_wires(wires)
    , m_numPermutations((size_t)(std::pow(2, wires.size() + 1) - 1))
{
  for (size_t i = 0; i < m_numPermutations; i++)
  {
    if (validationStrings.empty() || validatePermutation(i, validationStrings))
      m_validPermutationMasks.push_back(i);
  }
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
  str << "P[mask=" << mask << '\n';

  for (size_t i = 0; i < m_wires.size(); i++)
  {
    if (IS_ACTIVE_BIT)
      str << m_wires[i].first << " -> " << m_wires[i].second << '\n';
  }

  str << "]\n";
}

bool PermutationGenerator::validatePermutation(size_t mask, std::vector<std::string> searchStrings)
{
  bool valid = true;

  for (size_t i = 0; i < m_wires.size(); i++)
  {
    if (IS_ACTIVE_BIT)
    {
      // TODO
    }
  }

  return valid;
}
}