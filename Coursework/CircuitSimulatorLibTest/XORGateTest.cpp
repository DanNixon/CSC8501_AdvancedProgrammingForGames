#include "CppUnitTest.h"

#include "CircuitSimulatorLib/XORGate.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CircuitSimulator
{
namespace Test
{
TEST_CLASS(XORGateTest)
{
public:
  TEST_METHOD(XORGate_Evaluation_00)
  {
    XORGate g("xor");
    g.setInput("a", false);
    g.setInput("b", false);
    Assert::AreEqual(false, g.getInput("a"));
    Assert::AreEqual(false, g.getInput("b"));
    Assert::AreEqual(false, g.getOutput("z"));
  }

  TEST_METHOD(XORGate_Evaluation_10)
  {
    XORGate g("xor");
    g.setInput("a", true);
    g.setInput("b", false);
    Assert::AreEqual(true, g.getInput("a"));
    Assert::AreEqual(false, g.getInput("b"));
    Assert::AreEqual(true, g.getOutput("z"));
  }

  TEST_METHOD(XORGate_Evaluation_01)
  {
    XORGate g("xor");
    g.setInput("a", false);
    g.setInput("b", true);
    Assert::AreEqual(false, g.getInput("a"));
    Assert::AreEqual(true, g.getInput("b"));
    Assert::AreEqual(true, g.getOutput("z"));
  }

  TEST_METHOD(XORGate_Evaluation_11)
  {
    XORGate g("xor");
    g.setInput("a", true);
    g.setInput("b", true);
    Assert::AreEqual(true, g.getInput("a"));
    Assert::AreEqual(true, g.getInput("b"));
    Assert::AreEqual(false, g.getOutput("z"));
  }
};
}
}