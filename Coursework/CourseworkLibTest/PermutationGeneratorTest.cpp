#include "CppUnitTest.h"

#include <vector>

#include "CourseworkLib/Permutation.h"
#include "CourseworkLib/PermutationGenerator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace CircuitSimulator;

namespace Coursework
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

    {
      Permutation p = g.permutation(0);
      Assert::AreEqual((size_t)6, p.numWires());

      Assert::AreEqual(std::string("a1"), p.wire(0).first);
      Assert::AreEqual(std::string("b1"), p.wire(0).second);

      Assert::AreEqual(std::string("a2"), p.wire(1).first);
      Assert::AreEqual(std::string("b2"), p.wire(1).second);

      Assert::AreEqual(std::string("a3"), p.wire(2).first);
      Assert::AreEqual(std::string("b3"), p.wire(2).second);

      Assert::AreEqual(std::string("a4"), p.wire(3).first);
      Assert::AreEqual(std::string("b4"), p.wire(3).second);

      Assert::AreEqual(std::string("c1"), p.wire(4).first);
      Assert::AreEqual(std::string("d1"), p.wire(4).second);

      Assert::AreEqual(std::string("c2"), p.wire(5).first);
      Assert::AreEqual(std::string("d2"), p.wire(5).second);
    }

    {
      Permutation p = g.permutation(1);
      Assert::AreEqual((size_t)6, p.numWires());

      Assert::AreEqual(std::string("a1"), p.wire(0).first);
      Assert::AreEqual(std::string("b1"), p.wire(0).second);

      Assert::AreEqual(std::string("a2"), p.wire(1).first);
      Assert::AreEqual(std::string("b2"), p.wire(1).second);

      Assert::AreEqual(std::string("a3"), p.wire(2).first);
      Assert::AreEqual(std::string("b3"), p.wire(2).second);

      Assert::AreEqual(std::string("a4"), p.wire(3).first);
      Assert::AreEqual(std::string("b4"), p.wire(3).second);

      Assert::AreEqual(std::string("c1"), p.wire(4).first);
      Assert::AreEqual(std::string("d2"), p.wire(4).second);

      Assert::AreEqual(std::string("c2"), p.wire(5).first);
      Assert::AreEqual(std::string("d1"), p.wire(5).second);
    }

    {
      Permutation p = g.permutation(40);
      Assert::AreEqual((size_t)6, p.numWires());

      Assert::AreEqual(std::string("a1"), p.wire(0).first);
      Assert::AreEqual(std::string("b4"), p.wire(0).second);

      Assert::AreEqual(std::string("a2"), p.wire(1).first);
      Assert::AreEqual(std::string("b2"), p.wire(1).second);

      Assert::AreEqual(std::string("a3"), p.wire(2).first);
      Assert::AreEqual(std::string("b1"), p.wire(2).second);

      Assert::AreEqual(std::string("a4"), p.wire(3).first);
      Assert::AreEqual(std::string("b3"), p.wire(3).second);

      Assert::AreEqual(std::string("c1"), p.wire(4).first);
      Assert::AreEqual(std::string("d1"), p.wire(4).second);

      Assert::AreEqual(std::string("c2"), p.wire(5).first);
      Assert::AreEqual(std::string("d2"), p.wire(5).second);
    }

    {
      Permutation p = g.permutation(41);
      Assert::AreEqual((size_t)6, p.numWires());

      Assert::AreEqual(std::string("a1"), p.wire(0).first);
      Assert::AreEqual(std::string("b4"), p.wire(0).second);

      Assert::AreEqual(std::string("a2"), p.wire(1).first);
      Assert::AreEqual(std::string("b2"), p.wire(1).second);

      Assert::AreEqual(std::string("a3"), p.wire(2).first);
      Assert::AreEqual(std::string("b1"), p.wire(2).second);

      Assert::AreEqual(std::string("a4"), p.wire(3).first);
      Assert::AreEqual(std::string("b3"), p.wire(3).second);

      Assert::AreEqual(std::string("c1"), p.wire(4).first);
      Assert::AreEqual(std::string("d2"), p.wire(4).second);

      Assert::AreEqual(std::string("c2"), p.wire(5).first);
      Assert::AreEqual(std::string("d1"), p.wire(5).second);
    }
  }
};
}
}