/** @file */

#pragma once

#include "CircuitSimulatorLib/Wire.h"

#include "Permutation.h"

namespace Coursework1
{
class PermutationGenerator
{
public:
  static void GenerateWireList(const std::vector<std::string> & sourceList, const std::vector<std::string> &destList, CircuitSimulator::WireDefList &output);

public:
  typedef std::vector<size_t> IndexList;
  typedef IndexList::const_iterator IndexList_const_iter;

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