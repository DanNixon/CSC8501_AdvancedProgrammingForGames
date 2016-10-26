/** @file */

#pragma once

#include <memory>

namespace CircuitSimulator
{
class Circuit;

/**
 * @brief Shared pointer to a Circuit.
 */
typedef std::shared_ptr<Circuit> Circuit_ptr;

/**
 * @brief Shared pointee to a const Circuit.
 */
typedef std::shared_ptr<const Circuit> Circuit_const_ptr;
}
