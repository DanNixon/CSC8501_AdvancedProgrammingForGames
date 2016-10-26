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

  typedef std::map<S, std::pair<double, S>> Record;

public:
  static void FindPath(States &x, const Observations &o, const States &s, const Observations &y,
                       const TransitionMatrix &a, const EmissionMatrix &b,
                       const InitialProbability &pi)
  {
    std::vector<Record> t;

    // Initial state
    t.push_back(Record());
    for (S st : s)
    {
      // Product of initial and emission probabilities
      t[0][st].first = pi.at(st) * b.at({st, o[0]});

      // No pervious state
      t[0][st].second = S();
    }

    // Run Viterbi over observations
    for (size_t i = 1; i < o.size(); i++)
    {
      t.push_back(Record());

      for (S st : s)
      {
        // Find maximum transition probability
        double maxTrProb = 0.0;
        for (S pst : s)
        {
          double trProb = t[i - 1][pst].first * a.at({pst, st});

          if (trProb > maxTrProb)
            maxTrProb = trProb;
        }

        // Find most likely state
        for (S pst : s)
        {
          if (AreClose(t[i - 1][pst].first * a.at({pst, st}), maxTrProb))
          {
            t[i][st].first = maxTrProb * b.at({st, o[i]});
            t[i][st].second = pst;
            break;
          }
        }
      }
    }

    // Find most likely end state
    double maxProb = 0.0;
    S maxProbState;

    for (auto it = t.back().begin(); it != t.back().end(); ++it)
    {
      if (it->second.first > maxProb)
      {
        maxProb = it->second.first;
        maxProbState = it->first;
      }
    }

    x.push_back(maxProbState);

    // Backtrack to obtain path
    for (size_t i = t.size() - 1; i > 0; i--)
      x.push_back(t[i][x.back()].second);

    // Reverse list to get path in correct order
    std::reverse(x.begin(), x.end());
  }

private:
  static bool AreClose(double a, double b)
  {
    return std::abs(a - b) < 1e-6;
  }
};
}