#pragma once

#include <string>
#include <vector>

namespace Utility
{
class StringUtils
{
public:
  static void Split(std::vector<std::string> &subStrs, const std::string &str,
                    char delim);
};
}
