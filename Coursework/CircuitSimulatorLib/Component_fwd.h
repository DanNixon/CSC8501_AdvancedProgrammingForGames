/** @file */

#pragma once

#include <memory>

namespace CircuitSimulator
{
class Component;

/**
 * @brief Shared pointer to a Component.
 */
typedef std::shared_ptr<Component> Component_ptr;

/**
 * @brief Shared pointer to a const Component.
 */
typedef std::shared_ptr<const Component> Component_const_ptr;

/**
 * @brief List of Component.
 */
typedef std::vector<Component_ptr> ComponentList;

/**
 * @brief Const iterator over a list of Component.
 */
typedef ComponentList::const_iterator ComponentList_const_iter;
}
