/** @file */

#include "StringUtils.h"

namespace Utility
{
/**
 * @brief Splits a string into tokens by a given delimiter.
 * @param subStrs Reference to vector to store tokens in
 * @param str String to split
 * @param delim Delimiter to split by
 */
void StringUtils::Split(std::vector<std::string> &subStrs, const std::string &str, char delim)
{
  if (str.length() == 0)
    return;

  size_t start = 0;
  size_t end;
  while ((end = str.find(delim, start)) != std::string::npos)
  {
    if ((end - start) > 0)
      subStrs.push_back(str.substr(start, end - start));
    start = end + 1;
  }

  if (str.find(delim, start) == std::string::npos && start < str.length())
    subStrs.push_back(str.substr(start));
}
}
