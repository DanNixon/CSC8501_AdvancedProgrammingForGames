#include "CppUnitTest.h"

#include "CircuitSimulatorLib/Encoder.h"
#include "CircuitSimulatorLib/RegisterArray.h"
#include "CircuitSimulatorLib/XORGate.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CircuitSimulator
{
namespace Test
{
TEST_CLASS(EncoderTest)
{
public:
  TEST_METHOD(Encoder_Evaluation)
  {
    Encoder e;

    e.addComponent(new XORGate("xor1"));
    e.addComponent(new XORGate("xor2"));
    e.addComponent(new RegisterArray("r", 4));

    // Wiring as per example in CW spec
    e.wireUp("input_bus.bit_0", "r.bit_0");
    e.wireUp("input_bus.bit_0", "xor2.a");
    e.wireUp("r.bit_1", "xor2.b");
    e.wireUp("xor2.z", "output_bus.bit_1");
    e.wireUp("r.bit_2", "xor1.a");
    e.wireUp("r.bit_3", "xor1.b");
    e.wireUp("xor1.z", "output_bus.bit_0");

    Assert::AreEqual(false, e.getOutput("bit_0"));
    Assert::AreEqual(false, e.getOutput("bit_1"));

    std::vector<bool> inputBits = { true, false, false, true };
    std::vector<bool> expectedBits = { false, true, true, true, false, true, false, true }; // TODO

    Assert::IsTrue(expectedBits.size() == inputBits.size() * 2);

    auto expIt = expectedBits.begin();

    for (auto it = inputBits.begin(); it != inputBits.end(); ++it)
    {
      e.setInput("bit_0", *it);
      e.advanceRegisters(-1);

      Assert::AreEqual((bool) *it, e.getInput("bit_0"));

      Assert::AreEqual((bool) *(expIt++), e.getOutput("bit_0"));
      Assert::AreEqual((bool) *(expIt++), e.getOutput("bit_1"));
    }
  }
};
}
}