/** @file */

#pragma once

#include "CircuitSimulatorLib/Wire.h"

#include "Permutation.h"

namespace Coursework1
{
class PermutationGenerator
{
public:
  typedef std::vector<std::pair<std::vector<std::string>, std::vector<std::string>>>
      WireEndpointList;

public:
  PermutationGenerator(const WireEndpointList &wireEndpoints);
  virtual ~PermutationGenerator();

  size_t numPermutations() const;

  inline void reset()
  {
    m_groupPermutations.clear();
  }

  void generate();

  Permutation permutation(size_t idx);

private:
  const WireEndpointList &m_endpointGroups;
  std::vector<std::vector<std::vector<size_t>>> m_groupPermutations;
};
}