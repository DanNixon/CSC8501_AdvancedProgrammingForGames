/** @file */

#pragma once

#include <string>
#include <vector>

namespace Utility
{
/**
 * @class StringUtils
 * @author Dan Nixon
 * @brief Contains utility functions for string manipulation.
 */
class StringUtils
{
public:
  static void Split(std::vector<std::string> &subStrs, const std::string &str, char delim);
};
}
