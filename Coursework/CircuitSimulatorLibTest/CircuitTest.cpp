#include "CppUnitTest.h"

#include "CircuitSimulatorLib/Circuit.h"
#include "CircuitSimulatorLib/XORGate.h"
#include "CircuitSimulatorLib/RegisterArray.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CircuitSimulator
{
namespace Test
{
TEST_CLASS(CircuitTest)
{
public:
  TEST_METHOD(Circuit_Evaluation)
  {
    Circuit c({ "in1", "in2", "in3" }, { "out1", "out2", "out3" });

    c.addComponent(new XORGate("xor1"));

    c.wireUp("input_bus.in1", "xor1.a");
    c.wireUp("input_bus.in2", "xor1.b");
    c.wireUp("xor1.z", "output_bus.out1");
    c.wireUp("xor1.z", "output_bus.out2");
    c.wireUp("input_bus.in3", "output_bus.out3");

    Assert::IsTrue(c.validate());

    // Input 000
    c.setInput("in1", false);
    c.setInput("in2", false);
    c.setInput("in3", false);
    Assert::AreEqual(false, c.getOutput("out1"));
    Assert::AreEqual(false, c.getOutput("out2"));
    Assert::AreEqual(false, c.getOutput("out3"));

    // Input 001
    c.setInput("in1", false);
    c.setInput("in2", false);
    c.setInput("in3", true);
    Assert::AreEqual(false, c.getOutput("out1"));
    Assert::AreEqual(false, c.getOutput("out2"));
    Assert::AreEqual(true, c.getOutput("out3"));

    // Input 100
    c.setInput("in1", true);
    c.setInput("in2", false);
    c.setInput("in3", false);
    Assert::AreEqual(true, c.getOutput("out1"));
    Assert::AreEqual(true, c.getOutput("out2"));
    Assert::AreEqual(false, c.getOutput("out3"));

    // Input 010
    c.setInput("in1", false);
    c.setInput("in2", true);
    c.setInput("in3", false);
    Assert::AreEqual(true, c.getOutput("out1"));
    Assert::AreEqual(true, c.getOutput("out2"));
    Assert::AreEqual(false, c.getOutput("out3"));

    // Input 101
    c.setInput("in1", true);
    c.setInput("in2", false);
    c.setInput("in3", true);
    Assert::AreEqual(true, c.getOutput("out1"));
    Assert::AreEqual(true, c.getOutput("out2"));
    Assert::AreEqual(true, c.getOutput("out3"));

    // Input 011
    c.setInput("in1", false);
    c.setInput("in2", true);
    c.setInput("in3", true);
    Assert::AreEqual(true, c.getOutput("out1"));
    Assert::AreEqual(true, c.getOutput("out2"));
    Assert::AreEqual(true, c.getOutput("out3"));
  }

  TEST_METHOD(Circuit_Validation_XORCycle)
  {
    Circuit c({ "in1", "in2", "in3" }, { "out1", "out2", "out3" });

    c.addComponent(new XORGate("xor1"));
    c.addComponent(new XORGate("xor2"));

    c.wireUp("input_bus.in1", "xor1.a");
    c.wireUp("input_bus.in2", "xor2.b");
    c.wireUp("xor1.z", "xor2.a");
    c.wireUp("xor2.z", "xor1.b");
    c.wireUp("xor1.z", "output_bus.out1");
    c.wireUp("xor2.z", "output_bus.out2");
    c.wireUp("input_bus.in3", "output_bus.out3");

    Assert::IsFalse(c.validate());
  }

  TEST_METHOD(Circuit_Validation_BusCycle)
  {
    Circuit c({ "in1", "in2", "in3" }, { "out1", "out2", "out3" });

    c.wireUp("input_bus.in1", "input_bus.in2");
    c.wireUp("input_bus.in2", "output_bus.out1");

    Assert::IsFalse(c.validate());
  }

  TEST_METHOD(Circuit_Validation_RegisterArrayCycle)
  {
    Circuit c({ "in1", "in2", "in3" }, { "out1", "out2", "out3" });

    c.addComponent(new RegisterArray("r", 2));

    c.wireUp("input_bus.in1", "r.bit_0");
    c.wireUp("r.bit_0", "r.bit_1");
    c.wireUp("r.bit_1", "output_bus.out1");

    Assert::IsFalse(c.validate());
  }

  TEST_METHOD(Circuit_Validation_RegisterArrayShortCycle)
  {
    Circuit c({ "in1", "in2", "in3" }, { "out1", "out2", "out3" });

    c.addComponent(new RegisterArray("r", 2));

    c.wireUp("input_bus.in1", "r.bit_0");
    c.wireUp("r.bit_1", "r.bit_1");
    c.wireUp("r.bit_0", "output_bus.out1");

    Assert::IsFalse(c.validate());
  }
};
}
}