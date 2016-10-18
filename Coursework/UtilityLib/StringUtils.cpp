#include "StringUtils.h"

namespace Utility
{
void StringUtils::Split(std::vector<std::string> &subStrs,
                        const std::string &str, char delim)
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