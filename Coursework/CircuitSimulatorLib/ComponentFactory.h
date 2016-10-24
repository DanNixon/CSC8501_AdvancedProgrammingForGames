/** @file */

#pragma once

#include <string>
#include <vector>

#include "Component_fwd.h"

namespace CircuitSimulator
{
/**
 * @class ComponentFactory
 * @author Dan Nixon
 * @brief Provides instantiation of Component types from string parameters.
 */
class ComponentFactory
{
public:
  static Component_ptr Create(std::string name, const std::string &id,
                              std::vector<std::string> &args);
};
}
