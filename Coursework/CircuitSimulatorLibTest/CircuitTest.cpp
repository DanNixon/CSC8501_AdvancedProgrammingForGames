#include "CppUnitTest.h"

#include "CircuitSimulatorLib/Circuit.h"
#include "CircuitSimulatorLib/XORGate.h"

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
};
}
}