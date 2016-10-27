/** @file */

#pragma once

#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "CircuitSimulatorLib/BitStream.h"

#include "Permutation.h"

namespace Coursework
{
/**
 * @class DemonstrationWorkflow
 * @author Dan Nixon
 * @brief Contains a workflow that demonstrates the main features implemented in the coursework that
 *        can be executed over multiple threads.
 */
class DemonstrationWorkflow
{
public:
  static const std::string CLEAN_ENCODED_FILE_PATTERN;
  static const std::string NOISY_ENCODED_FILE_PATTERN;
  static const std::string WIRING_FILE_PATTERN;
  static const std::string TRELLIS_FILE_PATTERN;
  static const std::string CLEAN_DECODED_FILE_PATTERN;
  static const std::string NOISY_DECODED_FILE_PATTERN;

public:
  static void RunWorkflow(Permutation p, CircuitSimulator::BitStream inputData,
                          std::string filenameBase, std::ostream &out, std::mutex &outMutex);

public:
  DemonstrationWorkflow(std::ostream &out, const CircuitSimulator::BitStream &inputData);
  virtual ~DemonstrationWorkflow();

  void addJob(Permutation p, std::string filenameBase);
  void join();

private:
  std::ostream &m_out;   //!< Output stream for printing
  std::mutex m_outMutex; //!< Mutex used for single access to output stream (m_out)

  std::vector<std::thread> m_threads; //!< Vector of all threads

  const CircuitSimulator::BitStream m_inputData; //!< Copy of input data
};
}