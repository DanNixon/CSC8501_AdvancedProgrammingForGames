#include "CppUnitTest.h"

#include <string>

#include "Coursework2Lib/Viterbi.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Coursework2
{
namespace Test
{
TEST_CLASS(ViterbiTest)
{
public:
  TEST_METHOD(Viterbi_Example)
  {
    typedef Viterbi<std::string, std::string> StringViterbi;

    StringViterbi::Observations observationSpace = { "", "" };
    StringViterbi::States stateSpace = { "", "" };

    // TODO
  }
};
}
}