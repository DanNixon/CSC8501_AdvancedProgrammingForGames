/** @file */

#pragma once

#include <memory>

namespace CircuitSimulator
{
class Pin;
typedef std::shared_ptr<Pin> Pin_ptr;
typedef std::shared_ptr<const Pin> Pin_const_ptr;
}