/** @file */

#include "BitStreamComparator.h"

#include <algorithm>

#include "CircuitSimulatorLib/BitStream.h"
#include "UtilityLib/BinaryFileIO.h"

using namespace Utility;
using namespace CircuitSimulator;

namespace Coursework1
{
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

size_t BitStreamComparator::Compare(const std::string &aFilename, const std::string &bFilename)
{
  BitStream a;
  BitStream b;

  BinaryFileIO::ReadFile(a, aFilename);
  BinaryFileIO::ReadFile(b, bFilename);

  return Compare(a, b);
}

bool BitStreamComparator::CompareMultiple(const std::vector<BitStream> &data)
{
  for (auto it = data.cbegin() + 1; it != data.cend(); ++it)
  {
    if (Compare(data.front(), *it) > 0)
      return false;
  }

  return true;
}

bool BitStreamComparator::CompareMultiple(const std::vector<std::string> &filenames)
{
  std::vector<BitStream> data;
  LoadData(data, filenames);
  return CompareMultiple(data);
}

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

void BitStreamComparator::FindSimilar(IndexListList &results,
                                      const std::vector<std::string> &filenames)
{
  std::vector<BitStream> data;
  LoadData(data, filenames);
  FindSimilar(results, data);
}

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