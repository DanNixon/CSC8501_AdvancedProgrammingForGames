#include "CppUnitTest.h"

#include "CircuitSimulatorLib/Bus.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CircuitSimulator
{
namespace Test
{
TEST_CLASS(BusTest)
{
public:
  TEST_METHOD(Bus_Evaluation)
  {
    Bus b("bus", {"io1", "io2", "io3"});

    b.setInput("io1", true);
    b.setInput("io2", false);
    b.setInput("io3", true);

    Assert::AreEqual(true, b.getInput("io1"));
    Assert::AreEqual(false, b.getInput("io2"));
    Assert::AreEqual(true, b.getInput("io3"));

    Assert::AreEqual(true, b.getOutput("io1"));
    Assert::AreEqual(false, b.getOutput("io2"));
    Assert::AreEqual(true, b.getOutput("io3"));
  }
};
}
}