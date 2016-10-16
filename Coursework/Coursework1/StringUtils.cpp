#include "StringUtils.h"

void StringUtils::Split(std::vector<std::string> &subStrs,
                        const std::string &str, char delim)
{
  size_t start = 0;
  size_t end;
  while ((end = str.find(delim, start)) != std::string::npos)
  {
    subStrs.push_back(str.substr(start, end - start));
    start = end + 1;
  }
  subStrs.push_back(str.substr(start));
}