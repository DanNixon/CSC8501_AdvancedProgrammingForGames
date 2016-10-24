/** @file */

#pragma once

#include <vector>

#include "CircuitSimulatorLib/Circuit_fwd.h"

namespace Coursework1
{
class Permutation
{
public:
  static size_t GenerateAll(std::vector<Permutation>, CircuitSimulator::Circuit_const_ptr c);

public:
  typedef std::vector<std::pair<std::string, std::string>> WiringList;
  typedef WiringList::iterator WiringList_iter;
  typedef WiringList::const_iterator WiringList_const_iter;

public:
  Permutation();
  virtual ~Permutation();

  void apply(CircuitSimulator::Circuit_ptr c);

  friend std::ostream &operator<<(std::ostream &stream, const Permutation &o);

private:
  WiringList m_wiring;
};
}