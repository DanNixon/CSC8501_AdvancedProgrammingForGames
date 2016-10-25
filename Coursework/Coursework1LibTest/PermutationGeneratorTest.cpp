#include "CppUnitTest.h"

#include <vector>

#include "Coursework1Lib/Permutation.h"
#include "Coursework1Lib/PermutationGenerator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace CircuitSimulator;

namespace Coursework1
{
namespace Test
{
TEST_CLASS(PermutationGeneratorTest)
{
public:
  TEST_METHOD(Permutations)
  {
    WireDef w1("a1", "b1");
    WireDef w2("a1", "b2");
    WireDef w3("a1", "b3");
    WireDef w4("b1", "c1");
    WireDef w5("b1", "c2");
    WireDef w6("b2", "c2");
    WireDef w7("b2", "c3");
    WireDef w8("b2", "c4");

    WireDefList wires = { w1, w2, w3, w4, w5, w6, w7, w8 };

    // TODO
  }
};
}
}