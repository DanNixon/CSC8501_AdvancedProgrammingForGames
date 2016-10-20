#include "CppUnitTest.h"

#include "UtilityLib/BinaryFileIO.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utility
{
namespace Test
{
TEST_CLASS(BinaryFileIOTest)
{
public:
  TEST_METHOD(Stream_Out)
  {
    std::vector<bool> bits = {true, false, false, true, true, false, true, true};
    const std::string expected("10011011");

    std::stringstream out;

    Assert::AreEqual(bits.size() , BinaryFileIO::Write(bits, out));
    Assert::AreEqual(expected, out.str());
  }

  TEST_METHOD(Stream_In)
  {
    const std::string inStr("10011011");
    const std::vector<bool> expected = { true, false, false, true, true, false, true, true };

    std::stringstream in;
    in << inStr;

    std::vector<bool> bits;
    Assert::AreEqual(inStr.length(), BinaryFileIO::Read(bits, in));
    Assert::AreEqual(expected.size(), bits.size());

    auto tIt = bits.begin();
    for (auto it = expected.begin(); it != expected.end(); ++it)
      Assert::AreEqual((bool) *it, (bool) *(tIt++));
  }
};
}
}
