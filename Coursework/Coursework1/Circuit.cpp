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

void Circuit::patch(const std::string &from, const std::string &to)
{
  auto source = findPatchEndpoint(from);
  auto dest = findPatchEndpoint(to);
  m_wiring.push_back(
      new Wire(source.first, source.second, dest.first, dest.second));
}

std::pair<Component *, Pin *> Circuit::findPatchEndpoint(const std::string &def)
{
  std::vector<std::string> tokens;
  stringSplit(tokens, def, '.');

  auto compIt =
      std::find_if(m_components.begin(), m_components.end(),
                   [tokens](Component *c) { return c->id() == tokens[0]; });
  if (compIt == m_components.end())
    throw std::runtime_error("Could not find component \"" + tokens[0] + "\"");

  return std::make_pair(*compIt, (*compIt)->pin(tokens[1]));
}

std::ostream &operator<<(std::ostream &stream, const Circuit &o)
{
  stream << "Circuit[\n"
         << " Components:\n";
  for (auto it = o.m_components.begin(); it != o.m_components.end(); ++it)
    stream << " - " << *(*it) << '\n';

  stream << " Wiring:\n";
  for (auto it = o.m_wiring.begin(); it != o.m_wiring.end(); ++it)
    stream << " - " << *(*it) << '\n';

  stream << ']';

  return stream;
}
