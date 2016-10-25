#include "CppUnitTest.h"

#include <vector>

#include "Coursework1Lib/Permutation.h"
#include "Coursework1Lib/PermutationGenerator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace CircuitSimulator;

#define WIRES_EQUAL(e, v)                                                                          \
  {                                                                                                \
    Assert::AreEqual(e.first, v.first);                                                            \
    Assert::AreEqual(e.second, v.second);                                                          \
  }

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

    PermutationGenerator g(wires);
    Assert::AreEqual((size_t)256, g.numPermutations());

    // 0 should give no wires
    Permutation p0 = g.permutation(0);
    Assert::AreEqual((size_t)0, p0.numWires());

    // Max (all bits set) should give all wires
    Permutation pMax = g.permutation(std::numeric_limits<size_t>::max());
    Assert::AreEqual((size_t)8, pMax.numWires());
    WIRES_EQUAL(w1, pMax.wire(0));
    WIRES_EQUAL(w2, pMax.wire(1));
    WIRES_EQUAL(w3, pMax.wire(2));
    WIRES_EQUAL(w4, pMax.wire(3));
    WIRES_EQUAL(w5, pMax.wire(4));
    WIRES_EQUAL(w6, pMax.wire(5));
    WIRES_EQUAL(w7, pMax.wire(6));
    WIRES_EQUAL(w8, pMax.wire(7));

    // Even bits
    Permutation pA = g.permutation(0b10101010);
    Assert::AreEqual((size_t)4, pA.numWires());
    WIRES_EQUAL(w2, pA.wire(0));
    WIRES_EQUAL(w4, pA.wire(1));
    WIRES_EQUAL(w6, pA.wire(2));
    WIRES_EQUAL(w8, pA.wire(3));

    // Odd bits
    Permutation pB = g.permutation(0b01010101);
    Assert::AreEqual((size_t)4, pB.numWires());
    WIRES_EQUAL(w1, pB.wire(0));
    WIRES_EQUAL(w3, pB.wire(1));
    WIRES_EQUAL(w5, pB.wire(2));
    WIRES_EQUAL(w7, pB.wire(3));
  }
};
}
}