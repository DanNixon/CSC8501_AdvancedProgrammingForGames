#include "CppUnitTest.h"

#include "UtilityLib/StringUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utility
{
namespace Test
{
TEST_CLASS(StringUtilsTest)
{
public:
  TEST_METHOD(Split_EmptyString)
  {
    std::vector<std::string> tokens;
    StringUtils::Split(tokens, "", ',');
    Assert::AreEqual((size_t) 0, tokens.size());
  }

  TEST_METHOD(Split_SingleSubstr)
  {
    std::vector<std::string> tokens;
    StringUtils::Split(tokens, "test", ',');
    Assert::AreEqual((size_t)1, tokens.size());
    Assert::AreEqual(std::string("test"), tokens[0]);
  }

  TEST_METHOD(Split_MultipleSubstr)
  {
    std::vector<std::string> tokens;
    StringUtils::Split(tokens, "test,one,two", ',');
    Assert::AreEqual((size_t)3, tokens.size());
    Assert::AreEqual(std::string("test"), tokens[0]);
    Assert::AreEqual(std::string("one"), tokens[1]);
    Assert::AreEqual(std::string("two"), tokens[2]);
  }

  TEST_METHOD(Split_MultipleDelims)
  {
    std::vector<std::string> tokens;
    StringUtils::Split(tokens, "test,,one,two,,", ',');
    Assert::AreEqual((size_t)3, tokens.size());
    Assert::AreEqual(std::string("test"), tokens[0]);
    Assert::AreEqual(std::string("one"), tokens[1]);
    Assert::AreEqual(std::string("two"), tokens[2]);
  }
};
}
}