#include "CppUnitTest.h"

#include "CircuitSimulatorLib/RegisterArray.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CircuitSimulator
{
namespace Test
{
TEST_CLASS(RegisterArrayTest)
{
public:
  TEST_METHOD(RegisterArray_Evaluation)
  {
    RegisterArray r("register", 4);

    r.setInput("bit_0", false);
    r.setInput("bit_1", true);
    r.setInput("bit_2", false);
    r.setInput("bit_3", true);

    Assert::AreEqual(false, r.getInput("bit_0"));
    Assert::AreEqual(true, r.getInput("bit_1"));
    Assert::AreEqual(false, r.getInput("bit_2"));
    Assert::AreEqual(true, r.getInput("bit_3"));

    Assert::AreEqual(false, r.getOutput("bit_0"));
    Assert::AreEqual(true, r.getOutput("bit_1"));
    Assert::AreEqual(false, r.getOutput("bit_2"));
    Assert::AreEqual(true, r.getOutput("bit_3"));
  }

  TEST_METHOD(RegisterArray_ShiftLeft)
  {
    RegisterArray r("register", 4);

    r.setInput("bit_0", false);
    r.setInput("bit_1", true);
    r.setInput("bit_2", false);
    r.setInput("bit_3", false);

    r.shiftLeft();

    Assert::AreEqual(false, r.getInput("bit_0"));
    Assert::AreEqual(false, r.getInput("bit_1"));
    Assert::AreEqual(true, r.getInput("bit_2"));
    Assert::AreEqual(false, r.getInput("bit_3"));

    Assert::AreEqual(false, r.getOutput("bit_0"));
    Assert::AreEqual(false, r.getOutput("bit_1"));
    Assert::AreEqual(true, r.getOutput("bit_2"));
    Assert::AreEqual(false, r.getOutput("bit_3"));
  }

  TEST_METHOD(RegisterArray_ShiftRight)
  {
    RegisterArray r("register", 4);

    r.setInput("bit_0", false);
    r.setInput("bit_1", true);
    r.setInput("bit_2", false);
    r.setInput("bit_3", false);

    r.shiftRight();

    Assert::AreEqual(true, r.getInput("bit_0"));
    Assert::AreEqual(false, r.getInput("bit_1"));
    Assert::AreEqual(false, r.getInput("bit_2"));
    Assert::AreEqual(false, r.getInput("bit_3"));

    Assert::AreEqual(true, r.getOutput("bit_0"));
    Assert::AreEqual(false, r.getOutput("bit_1"));
    Assert::AreEqual(false, r.getOutput("bit_2"));
    Assert::AreEqual(false, r.getOutput("bit_3"));
  }
};
}
}