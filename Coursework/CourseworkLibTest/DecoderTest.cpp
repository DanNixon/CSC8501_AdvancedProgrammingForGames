#include "CppUnitTest.h"

#include <string>

#include "CourseworkLib/Decoder.h"
#include "CircuitSimulatorLib/BitStream.h"
#include "UtilityLib/BinaryFileIO.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace CircuitSimulator;
using namespace Utility;

/* Test data taken from this example: https://www.youtube.com/watch?v=iPh-HKZyWN4 */

namespace Coursework
{
namespace Test
{
TEST_CLASS(DecoderTest)
{
public:
  TEST_METHOD(Decoder_Simple_BitArray)
  {
    // Data
    BitStream encodedInput = {
      true, true,
      true, false,
      true, true,
      true, true,
      false, true,
      false, true,
      true, true
    };

    BitStream expectedOutput = {true, false, false, true, true, false, false};

    // Trellis
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

    // Do decoding
    BitStream output;
    Decoder d(t);
    Assert::AreEqual((size_t)0, d.decode(encodedInput, output));

    // Test size
    Assert::AreEqual(expectedOutput.size(), output.size());

    // Test data
    for (size_t i = 0; i < expectedOutput.size(); i++)
    {
      std::wstring m = L"idx " + std::to_wstring(i);
      Assert::AreEqual((bool)expectedOutput[i], (bool)output[i], m.c_str());
    }
  }

  TEST_METHOD(Decoder_Simple_Str)
  {
    // Data
    std::vector<std::string> encodedInput = { "11", "10", "11", "11", "01", "01", "11" };
    BitStream expectedOutput = { true, false, false, true, true, false, false };

    // Trellis
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

    // Do decoding
    BitStream output;
    Decoder d(t);
    Assert::AreEqual((size_t)0, d.decode(encodedInput, output));

    // Test size
    Assert::AreEqual(expectedOutput.size(), output.size());

    // Test data
    for (size_t i = 0; i < expectedOutput.size(); i++)
    {
      std::wstring m = L"idx " + std::to_wstring(i);
      Assert::AreEqual((bool)expectedOutput[i], (bool)output[i], m.c_str());
    }
  }
};
}
}