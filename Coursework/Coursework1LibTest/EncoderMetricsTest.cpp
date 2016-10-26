#include "CppUnitTest.h"

#include <vector>

#include "CircuitSimulatorLib/RegisterArray.h"
#include "CircuitSimulatorLib/XORGate.h"

#include "Coursework1Lib/EncoderMetrics.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace CircuitSimulator;

namespace Coursework1
{
namespace Test
{
TEST_CLASS(EncoderMetricsTest)
{
public:
  TEST_METHOD(Encoder_Metrics)
  {
    // Static seed for deterministic results
    std::srand(0);

    BitStream data;
    EncoderMetrics::GenerateRandomData(data, 100);

    Encoder_ptr e = std::make_shared<Encoder>();

    e->addComponent(std::make_shared<XORGate>("xor1"));
    e->addComponent(std::make_shared<XORGate>("xor2"));
    e->addComponent(std::make_shared<RegisterArray>("r", 4));

    // Wiring as per example in CW spec
    e->attachWire("input_bus.bit_0", "r.bit_0");
    e->attachWire("input_bus.bit_0", "xor2.a");
    e->attachWire("r.bit_1", "xor2.b");
    e->attachWire("xor2.z", "output_bus.bit_0");
    e->attachWire("r.bit_2", "xor1.a");
    e->attachWire("r.bit_3", "xor1.b");
    e->attachWire("xor1.z", "output_bus.bit_1");

    EncoderMetrics metrics(e);
    metrics.measure(data);
  }
};
}
}