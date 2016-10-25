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
  // List of pairs of pins to map and pins to map them to (must be equal length)
  const WireEndpointList &m_endpointGroups;

  // List of permutation indices for each endpoint group
  std::vector<std::vector<std::vector<size_t>>> m_groupPermutations;
};
}