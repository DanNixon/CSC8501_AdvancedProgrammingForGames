/** @file */

#pragma once

#include <map>
#include <vector>

namespace Coursework2
{
template <typename S, typename O> class Viterbi
{
public:
  typedef std::vector<S> States;
  typedef std::vector<O> Observations;
  typedef std::map<std::pair<S, S>, double> TransitionMatrix;
  typedef std::map<std::pair<O, S>, double> EmissionMatrix;
  typedef std::map<S, double> InitialProbability;

public:
  static void FindPath(States &x, const Observations &o, const States &s, const Observations &y,
                       const TransitionMatrix &a, const EmissionMatrix &b,
                       const InitialProbability &pi)
  {
    // TODO
  }
};
}