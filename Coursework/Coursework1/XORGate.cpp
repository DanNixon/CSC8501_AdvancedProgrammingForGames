#include "XORGate.h"

XORGate::XORGate(const std::string &id)
  : Device(id, "XOR Gate", {"a", "b"}, {"z"})
{
}

XORGate::~XORGate()
{
}

void XORGate::operate()
{
  m_outputs["z"] = m_inputs["a"] == m_inputs["b"];
}