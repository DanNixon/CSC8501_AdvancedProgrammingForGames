/** @file */

#include "Decoder.h"

#include <sstream>

namespace Coursework2
{
const Decoder::CDViterbi::States Decoder::STATE_SPACE = {true, false};
const Decoder::CDViterbi::InitialProbability Decoder::INITIAL_PROBABILITY = {{true, 0.5},
                                                                             {false, 0.5}};

Decoder::Decoder()
{
}

Decoder::~Decoder()
{
}

void Decoder::decode(const CircuitSimulator::BitStream &observations, CDViterbi::States &results)
{
  std::vector<std::string> strObs;
  strObs.reserve(observations.size() / 2);

  for (auto it = observations.cbegin(); it != observations.cend();)
  {
    std::stringstream o;
    o << *(it++) << *(it++);
    strObs.push_back(o.str());
  }

  decode(strObs, results);
}

void Decoder::decode(const CDViterbi::Observations &observations, CDViterbi::States &results)
{
  // clang-format off

  // TODO
  CDViterbi::TransitionMatrix tm = {
      {{true, true}, 0.5},
      {{true, false}, 0.5},
      {{false, true}, 0.5},
      {{false, false}, 0.5}
  };

  // TODO
  CDViterbi::EmissionMatrix em = {
      {{true, "00"}, 0.25},
      {{true, "01"}, 0.25},
      {{true, "10"}, 0.25},
      {{true, "11"}, 0.25},
      {{false, "00"}, 0.25},
      {{false, "01"}, 0.25},
      {{false, "10"}, 0.25},
      {{false, "11"}, 0.25}
  };

  // clang-format on

  CDViterbi::FindPath(results, STATE_SPACE, observations, tm, em, INITIAL_PROBABILITY);
}
}