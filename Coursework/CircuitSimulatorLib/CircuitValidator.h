/** @file */

#pragma once

#include "Circuit_fwd.h"

namespace CircuitSimulator
{
class CircuitValidator
{
public:
  static bool Validate(const Circuit *c);
};
}