/** @file */

#include "XORGate.h"

#include "Pin.h"

namespace CircuitSimulator
{
/**
 * @brief Creates an XORGate
 * @param id Unique string ID
 */
XORGate::XORGate(const std::string &id)
    : Component(id, "XOR Gate", {"a", "b"}, {"z"})
{
}

XORGate::~XORGate()
{
}

void XORGate::operate()
{
  bool a = pin("a")->getState();
  bool b = pin("b")->getState();
  pin("z")->setState(a != b);
}
}
