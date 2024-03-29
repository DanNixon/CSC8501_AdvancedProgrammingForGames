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

    e.addComponent(std::make_shared<XORGate>("xor1"));
    e.addComponent(std::make_shared<XORGate>("xor2"));
    e.addComponent(std::make_shared<RegisterArray>("r", 4));

    // Wiring as per example in CW spec
    e.attachWire("input_bus.bit_0", "r.bit_0");
    e.attachWire("input_bus.bit_0", "xor2.a");
    e.attachWire("r.bit_1", "xor2.b");
    e.attachWire("xor2.z", "output_bus.bit_0");
    e.attachWire("r.bit_2", "xor1.a");
    e.attachWire("r.bit_3", "xor1.b");
    e.attachWire("xor1.z", "output_bus.bit_1");

    Assert::IsTrue(e.validate());
    Assert::IsTrue(e.validateComponentUse());

    Assert::AreEqual(false, e.getOutput("bit_0"));
    Assert::AreEqual(false, e.getOutput("bit_1"));

    std::vector<bool> inputBits = { true, false, false, true };
    std::vector<bool> expectedBits = { true, false, true, false, false, true, true, true };

    Assert::AreEqual(expectedBits.size(), inputBits.size() * 2);

    auto expIt = expectedBits.begin();
    size_t i = 0;
    for (auto it = inputBits.begin(); it != inputBits.end(); ++it)
    {
      e.setInput("bit_0", *it);
      Assert::AreEqual((bool) *it, e.getInput("bit_0"));

      std::wstring m1 = L"idx " + std::to_wstring(i++);
      std::wstring m2 = L"idx " + std::to_wstring(i++);
      Assert::AreEqual((bool) *(expIt++), e.getOutput("bit_0"), m1.c_str());
      Assert::AreEqual((bool) *(expIt++), e.getOutput("bit_1"), m2.c_str());

      e.advanceRegisters(-1);
    }
  }

  TEST_METHOD(Encoder_Evaluation2)
  {
    Encoder e;

    e.addComponent(std::make_shared<XORGate>("xor1"));
    e.addComponent(std::make_shared<XORGate>("xor2"));
    e.addComponent(std::make_shared<RegisterArray>("r", 4));

    // Wiring as per example in CW spec
    e.attachWire("input_bus.bit_0", "r.bit_0");
    e.attachWire("input_bus.bit_0", "xor2.a");
    e.attachWire("r.bit_1", "xor2.b");
    e.attachWire("xor2.z", "output_bus.bit_0");
    e.attachWire("r.bit_2", "xor1.a");
    e.attachWire("r.bit_3", "xor1.b");
    e.attachWire("xor1.z", "output_bus.bit_1");

    Assert::IsTrue(e.validate());

    Assert::AreEqual(false, e.getOutput("bit_0"));
    Assert::AreEqual(false, e.getOutput("bit_1"));

    std::vector<bool> inputBits = { true, false, false, true };
    std::vector<bool> outputBits;
    std::vector<bool> expectedBits = { true, false, true, false, false, true, true, true };

    Assert::AreEqual(expectedBits.size(), inputBits.size() * 2);

    e.encode(inputBits, outputBits);

    Assert::AreEqual(expectedBits.size(), outputBits.size());

    auto expIt = expectedBits.begin();
    size_t i = 0;
    for (auto it = outputBits.begin(); it != outputBits.end(); ++it)
    {
      std::wstring m1 = L"idx " + std::to_wstring(i++);
      Assert::AreEqual((bool)*(expIt++), (bool)*it, m1.c_str());
    }
  }

  TEST_METHOD(Encoder_Trellis)
  {
    Encoder e;

    e.addComponent(std::make_shared<XORGate>("xor1"));
    e.addComponent(std::make_shared<XORGate>("xor2"));
    e.addComponent(std::make_shared<RegisterArray>("r", 4));

    // Wiring as per example in CW spec
    e.attachWire("input_bus.bit_0", "r.bit_0");
    e.attachWire("input_bus.bit_0", "xor2.a");
    e.attachWire("r.bit_1", "xor2.b");
    e.attachWire("xor2.z", "output_bus.bit_0");
    e.attachWire("r.bit_2", "xor1.a");
    e.attachWire("r.bit_3", "xor1.b");
    e.attachWire("xor1.z", "output_bus.bit_1");

    Assert::IsTrue(e.validate());
    Assert::IsTrue(e.validateComponentUse());

    Trellis t = e.generateTrellis();

    Assert::AreEqual((size_t)8, t.numStates());
    Assert::AreEqual((size_t)16, t.numMappings());

    // TODO
  }
};
}
}