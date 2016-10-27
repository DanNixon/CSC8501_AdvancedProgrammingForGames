#include "CppUnitTest.h"

#include <vector>

#include "CourseworkLib/BitStreamComparator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace CircuitSimulator;

namespace Coursework
{
namespace Test
{
TEST_CLASS(BitStreamComparatorTest)
{
public:
  TEST_METHOD(SingleComp)
  {
    BitStream a = { false, true, false, true };
    BitStream b = { false, true, false, true };
    BitStream c = { true, false, false, false };

    Assert::AreEqual((size_t)0, BitStreamComparator::Compare(a, b));
    Assert::AreEqual((size_t)0, BitStreamComparator::Compare(b, a));
    Assert::AreEqual((size_t)3, BitStreamComparator::Compare(c, b));
    Assert::AreEqual((size_t)3, BitStreamComparator::Compare(b, c));
  }

  TEST_METHOD(MultiComp)
  {
    BitStream a = { false, true, false, true };
    BitStream b = { false, true, false, true };
    BitStream c = { true, false, false, false };

    Assert::IsTrue(BitStreamComparator::CompareMultiple({ a, b }));
    Assert::IsFalse(BitStreamComparator::CompareMultiple({ a, b, c }));
  }

  TEST_METHOD(FindSimilar)
  {
    BitStream a = { false, true, false, true };
    BitStream b = { false, true, false, true };
    BitStream c = { true, false, false, false };
    BitStream d = { false, false, false, false };
    BitStream e = { true, false, false, false };

    BitStreamComparator::IndexListList results;
    BitStreamComparator::FindSimilar(results, { a, b, c, d, e });

    Assert::AreEqual((size_t)3, results.size());

    Assert::AreEqual((size_t)2, results[0].size());
    Assert::AreEqual((size_t)0, results[0][0]);
    Assert::AreEqual((size_t)1, results[0][1]);

    Assert::AreEqual((size_t)2, results[1].size());
    Assert::AreEqual((size_t)2, results[1][0]);
    Assert::AreEqual((size_t)4, results[1][1]);

    Assert::AreEqual((size_t)1, results[2].size());
    Assert::AreEqual((size_t)3, results[2][0]);
  }
};
}
}