/** @file */

#include "PermutationGenerator.h"

using namespace CircuitSimulator;

#define IS_ACTIVE_BIT (mask & (size_t)0x1 << i) > 0

namespace Coursework1
{
void PermutationGenerator::GenerateWireList(const std::vector<std::string> &sourceList,
                                            const std::vector<std::string> &destList,
                                            WireDefList &output)
{
  for (auto sIt = sourceList.cbegin(); sIt != sourceList.cend(); ++sIt)
  {
    for (auto dIt = destList.cbegin(); dIt != destList.cend(); ++dIt)
    {
      output.push_back(WireDef(*sIt, *dIt));
    }
  }
}

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
  str << "P[mask=" << mask << '\n';

  for (size_t i = 0; i < m_wires.size(); i++)
  {
    if (IS_ACTIVE_BIT)
      str << m_wires[i].first << " -> " << m_wires[i].second << '\n';
  }

  str << "]\n";
}
}