/** @file */

#include "PermutationGenerator.h"

#include <algorithm>
#include <numeric>

using namespace CircuitSimulator;

namespace Coursework1
{
PermutationGenerator::PermutationGenerator(const WireEndpointList &wireEndpoints)
    : m_endpointGroups(wireEndpoints)
{
}

PermutationGenerator::~PermutationGenerator()
{
}

size_t PermutationGenerator::numPermutations() const
{
  size_t count = 0;

  if (!m_groupPermutations.empty())
  {
    count = 1;

    for (auto it = m_groupPermutations.cbegin(); it != m_groupPermutations.cend(); ++it)
      count *= it->size();
  }

  return count;
}

void PermutationGenerator::generate()
{
  size_t i = 0;

  for (auto it = m_endpointGroups.cbegin(); it != m_endpointGroups.cend(); ++it)
  {
    if (it->first.size() != it->second.size())
      throw std::runtime_error("Size mismatch between endpoint group.");

    m_groupPermutations.push_back({});

    std::vector<size_t> groupIndices(it->first.size());
    std::iota(groupIndices.begin(), groupIndices.end(), 0);

    std::sort(groupIndices.begin(), groupIndices.end());
    do
    {
      m_groupPermutations[i].push_back(groupIndices);
    } while (std::next_permutation(groupIndices.begin(), groupIndices.end()));

    i++;
  }
}

Permutation PermutationGenerator::permutation(size_t idx)
{
  std::vector<size_t> sizes;
  for (auto it = m_groupPermutations.cbegin(); it != m_groupPermutations.cend(); ++it)
    sizes.push_back(it->size());

  // Get indices of each permutation segment to use
  // This section was written with reference to:
  // http://codinghighway.com/2014/02/22/c-multi-dimensional-arrays-part-2-flattened-to-unflattened-index
  std::vector<size_t> permutationIndices(sizes.size());
  permutationIndices.back() = 1;
  for (int i = sizes.size() - 2; i >= 0; i--)
    permutationIndices[i] = permutationIndices[i + 1] * sizes[i + 1];

  for (int i = 0; i < permutationIndices.size(); i++)
    permutationIndices[i] = (idx / permutationIndices[i]) % sizes[i];

  // Generate the wire list
  WireDefList wires;
  for (size_t i = 0; i < m_endpointGroups.size(); i++)
  {
    auto group = m_endpointGroups[i];
    for (size_t j = 0; j < group.first.size(); j++)
      wires.push_back(
          {group.first[j], group.second[m_groupPermutations[i][permutationIndices[i]][j]]});
  }
  
  return Permutation(wires);
}
}