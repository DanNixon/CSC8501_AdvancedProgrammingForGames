/** @file */

#pragma once

#include <memory>

namespace CircuitSimulator
{
class Pin;

/**
 * @brief Shared pointer to a Pin.
 */
typedef std::shared_ptr<Pin> Pin_ptr;

/**
 * @brief Shared pointer to a const Pin.
 */
typedef std::shared_ptr<const Pin> Pin_const_ptr;

/**
 * @brief List of Pin.
 */
typedef std::vector<Pin_ptr> PinList;

/**
 * @brief Const iterator over a list of Pin.
 */
typedef PinList::const_iterator PinList_const_iter;
}
