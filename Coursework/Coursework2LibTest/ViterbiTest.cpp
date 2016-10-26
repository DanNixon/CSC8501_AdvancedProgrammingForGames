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
    /* The exmaple from https://en.wikipedia.org/wiki/Viterbi_algorithm#Example */

    typedef Viterbi<std::string, std::string> StringViterbi;

    StringViterbi::States stateSpace = { "Healthy", "Feaver" };
    StringViterbi::Observations observations = { "normal", "cold", "dizzy" };

    StringViterbi::InitialProbability startProbability = {
      {"Healthy", 0.6},
      {"Feaver", 0.4}
    };

    StringViterbi::TransitionMatrix transMatrix = {
      { { "Healthy", "Healthy" }, 0.7 },
      { { "Healthy", "Feaver" }, 0.3 },
      { { "Feaver", "Healthy" }, 0.4 },
      { { "Feaver", "Feaver" }, 0.6 }
    };

    StringViterbi::EmissionMatrix emmMatrix = {
      { { "Healthy", "normal" }, 0.5 },
      { { "Healthy", "cold" }, 0.4 },
      { { "Healthy", "dizzy" }, 0.1 },
      { { "Feaver", "normal" }, 0.1 },
      { { "Feaver", "cold" }, 0.3 },
      { { "Feaver", "dizzy" }, 0.6 },
    };
    
    StringViterbi::States result;
    StringViterbi::FindPath(result, stateSpace, observations, transMatrix, emmMatrix, startProbability);

    Assert::AreEqual((size_t)3, result.size());
    Assert::AreEqual(std::string("Healthy"), result[0]);
    Assert::AreEqual(std::string("Healthy"), result[1]);
    Assert::AreEqual(std::string("Feaver"), result[2]);
  }
};
}
}