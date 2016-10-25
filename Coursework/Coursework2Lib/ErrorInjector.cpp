/** @file */

#include "ErrorInjector.h"

using namespace CircuitSimulator;

namespace Coursework2
{
const size_t ErrorInjector::BURST_RAND_MAX = 20;
const size_t ErrorInjector::BURST_RAND_THRESHOLD = 18;
const size_t ErrorInjector::BURST_LENGTH = 4;

void ErrorInjector::InjectError(const BitStream &in, BitStream &out)
{
  bool burstMode = false;
  size_t burstCounter = 0;

  for (auto inIt = in.cbegin(); inIt != in.cend(); ++inIt)
  {
    bool bit;
    if (burstMode)
    {
      bit = (std::rand() % 2) == 1;

      burstCounter++;
      if (burstCounter > BURST_LENGTH)
      {
        burstMode = false;
        burstCounter = 0;
      }
    }
    else
    {
      bit = *inIt;

      if (std::rand() % BURST_RAND_MAX > BURST_RAND_THRESHOLD)
        burstMode = true;
    }

    out.push_back(bit);
  }
}
}