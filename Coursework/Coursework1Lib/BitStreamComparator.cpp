/** @file */

#include "BitStreamComparator.h"

#include <algorithm>

#include "CircuitSimulatorLib/BitStream.h"
#include "UtilityLib/BinaryFileIO.h"

using namespace Utility;
using namespace CircuitSimulator;

namespace Coursework1
{
/**
 * @brief Check for similarity between two datasets.
 * @param a First dataset
 * @param b Second dataset
 * @return Hamming distance
 */
size_t BitStreamComparator::Compare(const BitStream &a, const BitStream &b)
{
  size_t mismatches = 0;

  auto aIt = a.cbegin();
  auto bIt = b.cbegin();

  while (aIt != a.cend() && bIt != b.cend())
  {
    if (*(aIt++) != *(bIt++))
      mismatches++;
  }

  if (!(aIt == a.cend() && bIt == b.cend()))
    mismatches += std::max(a.size(), b.size()) - std::min(a.size(), b.size());

  return mismatches;
}

/**
 * @brief Check for similarity between two datasets.
 * @param aFilename Filename to load first dataset from
 * @param bFilename Filename to load second dataset from
 * @return Hamming distance
 */
size_t BitStreamComparator::Compare(const std::string &aFilename, const std::string &bFilename)
{
  BitStream a;
  BitStream b;

  BinaryFileIO::ReadFile(a, aFilename);
  BinaryFileIO::ReadFile(b, bFilename);

  return Compare(a, b);
}

/**
 * @brief Compares multiple datasets and checks for identity.
 * @param data Vector of datasets
 * @return True if all datasets are identical
 */
bool BitStreamComparator::CompareMultiple(const std::vector<BitStream> &data)
{
  for (auto it = data.cbegin() + 1; it != data.cend(); ++it)
  {
    if (Compare(data.front(), *it) > 0)
      return false;
  }

  return true;
}

/**
 * @brief Compares multiple datasets and checks for identity.
 * @param filenames Vector of filenames to load datasets from
 * @return True if all datasets are identical
 */
bool BitStreamComparator::CompareMultiple(const std::vector<std::string> &filenames)
{
  std::vector<BitStream> data;
  LoadData(data, filenames);
  return CompareMultiple(data);
}

/**
 * @brief Searches for groups of identical datasets.
 * @param results Reference to list of results
 * @param data Vector of datasets
 */
void BitStreamComparator::FindSimilar(IndexListList &results, const std::vector<BitStream> &data)
{
  // For each input data set
  for (size_t inIdx = 0; inIdx < data.size(); inIdx++)
  {
    bool matchFound = false;

    // Check for a matching dataset already processed
    for (size_t fIdx = 0; !matchFound && fIdx < results.size(); fIdx++)
    {
      // If a match is found add the index to the list of matches
      if (Compare(data[inIdx], data[results[fIdx][0]]) == 0)
      {
        results[fIdx].push_back(inIdx);
        matchFound = true;
      }
    }

    // If no match then add this as another group of unique data
    if (!matchFound)
      results.push_back({inIdx});
  }
}

/**
 * @brief Searches for groups of identical datasets.
 * @param results Reference to list of results
 * @param filenames Vector of filenames to load datasets from
 */
void BitStreamComparator::FindSimilar(IndexListList &results,
                                      const std::vector<std::string> &filenames)
{
  std::vector<BitStream> data;
  LoadData(data, filenames);
  FindSimilar(results, data);
}

/**
 * @brief Loads multiple datasets from several files.
 * @param data Reference to vector to store datasets in
 * @param filenames Vector of filenames to load datasets from
 */
void BitStreamComparator::LoadData(std::vector<BitStream> &data,
                                   const std::vector<std::string> &filenames)
{
  for (auto it = filenames.cbegin(); it != filenames.cend(); ++it)
  {
    BitStream s;
    BinaryFileIO::ReadFile(s, *it);
    data.push_back(s);
  }
}
}
