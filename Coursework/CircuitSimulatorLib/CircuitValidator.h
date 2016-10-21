/** @file */

#pragma once

#include "Circuit_fwd.h"

namespace CircuitSimulator
{
class CircuitValidator
{
public:
  bool Validate(Circuit_ptr c);
};
}