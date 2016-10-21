/** @file */

#pragma once

#include <memory>

namespace CircuitSimulator
{
class Circuit;
typedef std::shared_ptr<Circuit> Circuit_ptr;
typedef std::shared_ptr<const Circuit> Circuit_const_ptr;
}