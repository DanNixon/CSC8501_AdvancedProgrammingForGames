/** @file */

#pragma once

#include <memory>

namespace CircuitSimulator
{
class Component;
typedef std::shared_ptr<Component> Component_ptr;
typedef std::shared_ptr<const Component> Component_const_ptr;
}