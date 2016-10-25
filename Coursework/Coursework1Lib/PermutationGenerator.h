/** @file */

#pragma once

#include "CircuitSimulatorLib/Wire.h"

#include "Permutation.h"

namespace Coursework1
{
class PermutationGenerator
{
public:
  typedef std::vector<size_t> IndexList;
  typedef IndexList::const_iterator IndexList_const_iter;

public:
  PermutationGenerator(const CircuitSimulator::WireDefList &wires,
                       const std::vector<std::string> &validationStrings);
  virtual ~PermutationGenerator();

  inline size_t numPermutations() const
  {
    return m_numPermutations;
  }

  inline size_t numValidPermutations() const
  {
    return m_validPermutationMasks.size();
  }

  inline IndexList_const_iter validMaskBegin() const
  {
    return m_validPermutationMasks.cbegin();
  }

  inline IndexList_const_iter validMaskEnd() const
  {
    return m_validPermutationMasks.cend();
  }

  Permutation permutation(size_t mask);
  void printPermutation(size_t mask, std::ostream &str);
  bool validatePermutation(size_t mask, std::vector<std::string> searchStrings);

private:
  const CircuitSimulator::WireDefList &m_wires;
  const size_t m_numPermutations;
  std::vector<size_t> m_validPermutationMasks;
};
}