#include "CppUnitTest.h"

#include "CircuitSimulatorLib/Wire.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CircuitSimulator
{
namespace Test
{
TEST_CLASS(WireTest)
{
public:
  TEST_METHOD(WireDef_StreamOut)
  {
    WireDef w("abc", "def");
    std::stringstream stream;

    stream << w;

    Assert::AreEqual(std::string("abc -> def"), stream.str());
  }

  TEST_METHOD(WireDef_StreamIn)
  {
    const std::string s("abc>def");

    std::stringstream stream(s);
    WireDef w;

    stream >> w;

    Assert::AreEqual(std::string("abc"), w.first);
    Assert::AreEqual(std::string("def"), w.second);
  }
};
}
}