/** @file */

#pragma once

#include "CircuitSimulatorLib/Wire.h"

#include "Permutation.h"

namespace Coursework1
{
/**
 * @class PermutationGenerator
 * @author Dan Nixon
 * @brief Class containing functionality ofr generating wiring permutations for encoders.
 */
class PermutationGenerator
{
public:
  /**
   * @brief Type containing sets of pins that are to be wired together.
   */
  typedef std::pair<std::vector<std::string>, std::vector<std::string>> WireEndpoint;

  /**
   * @brief List of wire endpoints.
   */
  typedef std::vector<WireEndpoint> WireEndpointList;

public:
  PermutationGenerator(const WireEndpointList &wireEndpoints);
  virtual ~PermutationGenerator();

  size_t numPermutations() const;

  /**
   * @brief Clears the permutations generted.
   */
  inline void reset()
  {
    m_groupPermutations.clear();
  }

  void generate();

  Permutation permutation(size_t idx);

private:
  const WireEndpointList m_endpointGroups; //!< List of pairs of pins to map and pins to map them to
                                           //(must be equal length)

  std::vector<std::vector<std::vector<size_t>>>
      m_groupPermutations; //!< List of permutation indices for each endpoint group
};
}
