#include "CppUnitTest.h"

#include <string>

#include "CircuitSimulatorLib/Trellis.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CircuitSimulator
{
namespace Test
{
TEST_CLASS(TrellisTest)
{
public:
  TEST_METHOD(Trellis_StreamOut)
  {
    Trellis t({
      { 0, false, "00", 0 },
      { 0, true, "11", 2 },
      { 1, false, "11", 0 },
      { 1, true, "00", 2 },
      { 2, false, "10", 1 },
      { 2, true, "01", 3 },
      { 3, false, "01", 1 },
      { 3, true, "10", 3 }
    });

    std::stringstream str;
    str << t;

    Assert::AreEqual((size_t)4, t.numStates());
    Assert::AreEqual((size_t)8, t.numMappings());

    Assert::AreEqual(std::string("0 - 0/00 - 0\n0 - 1/11 - 2\n1 - 0/11 - 0\n1 - 1/00 - 2\n2 - 0/10 - 1\n2 - 1/01 - 3\n3 - 0/01 - 1\n3 - 1/10 - 3\n"), str.str());
  }

  TEST_METHOD(Trellis_StreamIn)
  {
    std::stringstream in("0 - 0/00 - 0\n0 - 1/11 - 2\n1 - 0/11 - 0\n1 - 1/00 - 2\n2 - 0/10 - 1\n2 - 1/01 - 3\n3 - 0/01 - 1\n3 - 1/10 - 3\n");

    Trellis t;
    in >> t;

    Assert::AreEqual((size_t)4, t.numStates());
    Assert::AreEqual((size_t)8, t.numMappings());

    Assert::AreEqual(false, t.mapping(0).bit);
    Assert::AreEqual(std::string("00"), t.mapping(0).code);
    Assert::AreEqual((size_t) 0, t.mapping(0).srcState);
    Assert::AreEqual((size_t)0, t.mapping(0).destState);

    Assert::AreEqual(true, t.mapping(1).bit);
    Assert::AreEqual(std::string("11"), t.mapping(1).code);
    Assert::AreEqual((size_t)0, t.mapping(1).srcState);
    Assert::AreEqual((size_t)2, t.mapping(1).destState);

    Assert::AreEqual(false, t.mapping(6).bit);
    Assert::AreEqual(std::string("01"), t.mapping(6).code);
    Assert::AreEqual((size_t)3, t.mapping(6).srcState);
    Assert::AreEqual((size_t)1, t.mapping(6).destState);

    Assert::AreEqual(true, t.mapping(7).bit);
    Assert::AreEqual(std::string("10"), t.mapping(7).code);
    Assert::AreEqual((size_t)3, t.mapping(7).srcState);
    Assert::AreEqual((size_t)3, t.mapping(7).destState);
  }

  TEST_METHOD(Trellis_GetMappingForDestState)
  {
    Trellis t({
      { 0, false, "00", 0 },
      { 0, true, "11", 2 },
      { 1, false, "11", 0 },
      { 1, true, "00", 2 },
      { 2, false, "10", 1 },
      { 2, true, "01", 3 },
      { 3, false, "01", 1 },
      { 3, true, "10", 3 }
    });

    Assert::AreEqual((size_t)4, t.numStates());
    Assert::AreEqual((size_t)8, t.numMappings());

    {
      std::vector<TrellisMapping> res;
      t.getMappingsForDestinationState(res, 0);
      Assert::AreEqual((size_t)2, res.size());

      Assert::AreEqual(false, res[0].bit);
      Assert::AreEqual(std::string("00"), res[0].code);
      Assert::AreEqual((size_t)0, res[0].srcState);
      Assert::AreEqual((size_t)0, res[0].destState);

      Assert::AreEqual(false, res[1].bit);
      Assert::AreEqual(std::string("11"), res[1].code);
      Assert::AreEqual((size_t)1, res[1].srcState);
      Assert::AreEqual((size_t)0, res[1].destState);
    }

    {
      std::vector<TrellisMapping> res;
      t.getMappingsForDestinationState(res, 2);
      Assert::AreEqual((size_t)2, res.size());

      Assert::AreEqual(true, res[0].bit);
      Assert::AreEqual(std::string("11"), res[0].code);
      Assert::AreEqual((size_t)0, res[0].srcState);
      Assert::AreEqual((size_t)2, res[0].destState);

      Assert::AreEqual(true, res[1].bit);
      Assert::AreEqual(std::string("00"), res[1].code);
      Assert::AreEqual((size_t)1, res[1].srcState);
      Assert::AreEqual((size_t)2, res[1].destState);
    }
  }
};
}
}