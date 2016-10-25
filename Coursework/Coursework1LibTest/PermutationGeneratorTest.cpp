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
    PermutationGenerator::WireEndpointList ep = {
      {{"a1", "a2", "a3", "a4"}, {"b1", "b2", "b3", "b4"}},
      {{"c1", "c2"}, {"d1", "d2"}}
    };

    PermutationGenerator g(ep);
    g.generate();
    Assert::AreEqual((size_t)48, g.numPermutations());

    // TODO: test these results
    g.permutation(0);
    g.permutation(20);
    g.permutation(40);
    g.permutation(41);
  }
};
}
}