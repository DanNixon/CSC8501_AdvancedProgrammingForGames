#include "CppUnitTest.h"

#include <vector>

#include "Coursework1Lib/BitStreamComparator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Coursework1
{
namespace Test
{
TEST_CLASS(BitStreamComparatorTest)
{
public:
  TEST_METHOD(SingleComp)
  {
    BitStreamComparator::BitStream a = { false, true, false, true };
    BitStreamComparator::BitStream b = { false, true, false, true };
    BitStreamComparator::BitStream c = { true, false, false, false };

    Assert::AreEqual((size_t)0, BitStreamComparator::Compare(a, b));
    Assert::AreEqual((size_t)0, BitStreamComparator::Compare(b, a));
    Assert::AreEqual((size_t)3, BitStreamComparator::Compare(c, b));
    Assert::AreEqual((size_t)3, BitStreamComparator::Compare(b, c));
  }

  TEST_METHOD(MultiComp)
  {
    BitStreamComparator::BitStream a = { false, true, false, true };
    BitStreamComparator::BitStream b = { false, true, false, true };
    BitStreamComparator::BitStream c = { true, false, false, false };

    Assert::IsTrue(BitStreamComparator::CompareMultiple({ a, b }));
    Assert::IsFalse(BitStreamComparator::CompareMultiple({ a, b, c }));
  }

  TEST_METHOD(FindSimilar)
  {
    BitStreamComparator::BitStream a = { false, true, false, true };
    BitStreamComparator::BitStream b = { false, true, false, true };
    BitStreamComparator::BitStream c = { true, false, false, false };
    BitStreamComparator::BitStream d = { false, false, false, false };
    BitStreamComparator::BitStream e = { true, false, false, false };

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