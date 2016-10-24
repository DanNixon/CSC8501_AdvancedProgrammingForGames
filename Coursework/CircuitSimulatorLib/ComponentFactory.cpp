/** @file */

#include "ComponentFactory.h"

#include <algorithm>

#include "Bus.h"
#include "RegisterArray.h"
#include "XORGate.h"

namespace CircuitSimulator
{
/**
 * @brief Creates a Component from string parameters.
 * @param name Name of the component
 * @param id Unique string ID for the new instance
 * @param args LIst of additional string arguments required to create the component
 */
Component_ptr ComponentFactory::Create(std::string name, const std::string &id,
                                       std::vector<std::string> &args)
{
  std::transform(name.begin(), name.end(), name.begin(), tolower);

  Component_ptr c;

  if (name == "registerarray" && args.size() == 1)
    c = std::make_shared<RegisterArray>(id, std::stoi(args[0]));

  if (name == "xorgate")
    c = std::make_shared<XORGate>(id);

  return c;
}
}