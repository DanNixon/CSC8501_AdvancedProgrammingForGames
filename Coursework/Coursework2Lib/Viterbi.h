/** @file */

#pragma once

#include <map>
#include <vector>

// Derived from https://en.wikipedia.org/wiki/Viterbi_algorithm#Pseudocode

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
    size_t tLen = s.size();

    double ** t1 = new double*[tlen];
    double ** t2 = new double*[tlen];

    for (size_t i = 0; i < tlen; i++)
    {
      t1[i] = new double[tlen];
      t2[i] = new double[tlen];
    }

    // For each state s_i
    for (size_t i = 0; i < s.size(); i++)
    {
      t1[i][0] = pi.at(s.at(i)) * b.at({s.at(i), o.at(0)});
      t2[i][0] = 0.0;
    }

    // For elements of T
    for (size_t i = 1; i < tLen; i++)
    {
      // For each state s_j
      for (size_t j = 0; j < s.size(); j++)
      {
        // TODO
        t1[j][i] = 0.0;
        t2[j][i] = 0.0;
      }
    }

    // TODO: z_{T}\gets \arg \max _{k}{(T_{1}[k,T])}

    // TODO: xT <- szT

    for (size_t i = tLen; i > 0; i--)
    {
      // TODO
    }

    // TODO: Delete t1 and t2
  }
};
}