#include "Circuit.h"

#include <algorithm>

#include "Bus.h"

void stringSplit(std::vector<std::string> &subStrs, const std::string &str,
                 char delim)
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

Circuit::Circuit(std::list<std::string> inputs, std::list<std::string> outputs)
{
  m_components.push_back(new Bus("input_bus", inputs));
  m_components.push_back(new Bus("output_bus", outputs));
}

Circuit::~Circuit()
{
}

Component *Circuit::component(const std::string &name)
{
  auto it = std::find_if(m_components.begin(), m_components.end(),
                         [name](Component *c) { return c->id() == name; });

  if (it == m_components.end())
    throw std::runtime_error("Could not find component \"" + name + "\"");

  return *it;
}

const Component *Circuit::component(const std::string &name) const
{
  auto it = std::find_if(m_components.cbegin(), m_components.cend(),
                         [name](Component *c) { return c->id() == name; });

  if (it == m_components.cend())
    throw std::runtime_error("Could not find component \"" + name + "\"");

  return *it;
}

bool Circuit::hasComponent(const std::string &name) const
{
  auto it = std::find_if(m_components.cbegin(), m_components.cend(),
                         [name](Component *c) { return c->id() == name; });

  return it != m_components.cend();
}

void Circuit::patch(const std::string &from, const std::string &to)
{
  Pin *source = findPatchEndpoint(from);
  Pin *dest = findPatchEndpoint(to);
  source->wireTo(dest);
}

void Circuit::setInput(const std::string &name, bool value)
{
  Component *c = component("input_bus");
  c->setInput(name, value);
}

bool Circuit::getOutput(const std::string &name) const
{
  const Component *c = component("output_bus");
  return c->getOutput(name);
}

Pin *Circuit::findPatchEndpoint(const std::string &def)
{
  std::vector<std::string> tokens;
  stringSplit(tokens, def, '.');
  return component(tokens[0])->pin(tokens[1]);
}

std::ostream &operator<<(std::ostream &stream, const Circuit &o)
{
  stream << "Circuit[\n";

  for (auto it = o.m_components.begin(); it != o.m_components.end(); ++it)
    stream << " - " << *(*it) << '\n';

  stream << ']';

  return stream;
}
