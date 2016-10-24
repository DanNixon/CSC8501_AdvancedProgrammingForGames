/** @file */

#include "Circuit.h"

#include <algorithm>

#include "UtilityLib/StringUtils.h"

#include "Bus.h"
#include "CircuitValidator.h"
#include "Pin.h"

using namespace Utility;

namespace CircuitSimulator
{
const std::string Circuit::INPUT_BUS_NAME = "input_bus";
const std::string Circuit::OUTPUT_BUS_NAME = "output_bus";

/**
 * @brief Create a new component.
 * @param inputs List of input pin names
 * @param outputs List of output pin names
 */
Circuit::Circuit(std::vector<std::string> inputs, std::vector<std::string> outputs)
{
  m_components.push_back(std::make_shared<Bus>(INPUT_BUS_NAME, inputs));
  m_components.push_back(std::make_shared<Bus>(OUTPUT_BUS_NAME, outputs));
}

Circuit::~Circuit()
{
}

/**
 * @brief Adds a component to the circuit.
 * @param component Pointer to component
 */
void Circuit::addComponent(Component_ptr component)
{
  m_components.push_back(component);
}

/**
 * @brief Checks of a component exists in the circuit.
 * @param name Name of the component
 * @return True if a component with the given name exists
 */
bool Circuit::hasComponent(const std::string &name) const
{
  auto it = std::find_if(m_components.cbegin(), m_components.cend(),
                         [name](Component_const_ptr c) { return c->id() == name; });

  return it != m_components.cend();
}

/**
 * @brief Gets a component by name.
 * @param name Name of the component
 * @return Pointer to component
 */
Component_ptr Circuit::component(const std::string &name)
{
  auto it = std::find_if(m_components.begin(), m_components.end(),
                         [name](Component_ptr c) { return c->id() == name; });

  if (it == m_components.end())
    throw std::runtime_error("Could not find component \"" + name + "\"");

  return *it;
}

/**
 * @brief Gets a component by name.
 * @param name Name of the component
 * @return Const pointer to component
 */
Component_const_ptr Circuit::component(const std::string &name) const
{
  auto it = std::find_if(m_components.cbegin(), m_components.cend(),
                         [name](Component_const_ptr c) { return c->id() == name; });

  if (it == m_components.cend())
    throw std::runtime_error("Could not find component \"" + name + "\"");

  return *it;
}

/**
 * @brief Wires the output pin of one component to the input pin of another.
 * @param from Source pin
 * @param to Destination pin
 *
 * Source and destination are in format "[component name].[pin name]".
 */
void Circuit::attachWire(const std::string &from, const std::string &to)
{
  Pin_ptr source = findPatchEndpoint(from);
  Pin_ptr dest = findPatchEndpoint(to);
  Pin::AttachWire(source, dest);
}

/**
 * @brief Removes wiring betweem the output pin of one component to the input
 *        pin of another.
 * @param from Source pin
 * @param to Destination pin
 *
 * Source and destination are in format "[component name].[pin name]".
 */
void Circuit::removeWire(const std::string &from, const std::string &to)
{
  Pin_ptr source = findPatchEndpoint(from);
  Pin_ptr dest = findPatchEndpoint(to);
  Pin::RemoveWire(source, dest);
}

/**
 * @brief Validates the current configuration of the circuit.
 * @return True for a valid circuit
 *
 * A circuit is valid iff there are no cycles in the graph of component/pin
 * wiring.
 */
bool Circuit::validate() const
{
  return CircuitValidator::Validate(this);
}

/**
 * @brief Sets the value of a pin on the input bus.
 * @param name Input name
 * @param value Value
 */
void Circuit::setInput(const std::string &name, bool value)
{
  Component_ptr c = component("input_bus");
  c->setInput(name, value);
}

/**
 * @brief Gets the value of a pin on the input bus.
 * @param name Input name
 * @return Pin value
 */
bool Circuit::getInput(const std::string &name) const
{
  Component_const_ptr c = component("input_bus");
  return c->getOutput(name);
}

/**
 * @brief Gets the value of a pin on the output bus.
 * @param name Output name
 * @return Pin value
 */
bool Circuit::getOutput(const std::string &name) const
{
  Component_const_ptr c = component("output_bus");
  return c->getOutput(name);
}

/**
 * @brief Finds the pin to connect a wire to.
 * @param def Pin name
 * @return Pointer to pin
 * @see attachWire()
 * @see removeWire()
 */
Pin_ptr Circuit::findPatchEndpoint(const std::string &def)
{
  std::vector<std::string> tokens;
  StringUtils::Split(tokens, def, '.');
  return component(tokens[0])->pin(tokens[1]);
}

/**
 * @brief Output a Circuit to a stream as a friendly formatted string.
 * @param stream Reference to output stream
 * @param o Circuit to output
 * @return Reference to output stream
 */
std::ostream &operator<<(std::ostream &stream, const Circuit &o)
{
  stream << "Circuit[\n";

  for (auto it = o.m_components.begin(); it != o.m_components.end(); ++it)
    stream << " - " << *(*it) << '\n';

  stream << ']';

  return stream;
}
}
