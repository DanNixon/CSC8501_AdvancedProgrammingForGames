/** @file */

#include "XORGate.h"

namespace CircuitSimulator
{
XORGate::XORGate(const std::string &id)
    : Component(id, "XOR Gate", {"a", "b"}, {"z"})
{
}

XORGate::~XORGate()
{
}

void XORGate::operate()
{
  pin("z")->setState(pin("a")->getState() != pin("b")->getState());
}
}
