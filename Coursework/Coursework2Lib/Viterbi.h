/** @file */

#pragma once

#include <map>
#include <vector>

namespace Coursework2
{
/**
 * @class Viterbi
 * @author Dan Nixon
 * @brief Templated class for performing the Viterbi algorithm.
 */
template <typename S, typename O> class Viterbi
{
public:
  /**
   * @brief Container of states.
   *
   * Flat vector of states.
   */
  typedef std::vector<S> States;

  /**
   * @brief Container of observations.
   *
   * Flat vector of observations.
   */
  typedef std::vector<O> Observations;

  /**
   * @brief Container of transition matrix.
   *
   * Map of two states to the probability of transition from the first state to the second.
   */
  typedef std::map<std::pair<S, S>, double> TransitionMatrix;

  /**
   * @brief Container of emission matrix.
   *
   * Map of observation and state to the probability of that state given that observation.
   */
  typedef std::map<std::pair<O, S>, double> EmissionMatrix;

  /**
   * @brief Container of initial probabilities.
   *
   * Map of state to initial probability of that state.
   */
  typedef std::map<S, double> InitialProbability;

  /**
   * @brief Used to record an iteration of the Viterbi algorithm.
   */
  typedef std::map<S, std::pair<double, S>> Record;

public:
  /**
   * @brief Finds the most likely path using the Viterbi algorithm.
   * @param x Output path
   * @param o Observation space
   * @param s State space
   * @param y Observations
   * @param a Transition matrix
   * @param b Emission matrix
   * @param pi Initial state probabilities
   *
   * Derived from https://en.wikipedia.org/wiki/Viterbi_algorithm#Pseudocode
   */
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
  /**
   * @brief Helper function to test if two doubles are close.
   * @param a First value
   * @param b Second value
   * @return True of values differ by less than 1e-6.
   */
  static bool AreClose(double a, double b)
  {
    return std::abs(a - b) < 1e-6;
  }
};
}
