/** @file */

#include "DemonstrationWorkflow.h"

#include <fstream>

#include "CircuitSimulatorLib/Encoder.h"
#include "CircuitSimulatorLib/XORGate.h"
#include "CourseworkLib/Decoder.h"
#include "CourseworkLib/ErrorInjector.h"
#include "UtilityLib/BinaryFileIO.h"

#include "BitStreamComparator.h"

using namespace CircuitSimulator;
using namespace Utility;

namespace Coursework
{
const std::string DemonstrationWorkflow::CLEAN_ENCODED_FILE_PATTERN = "_encoded.txt";
const std::string DemonstrationWorkflow::NOISY_ENCODED_FILE_PATTERN = "_encoded_noisy.txt";
const std::string DemonstrationWorkflow::WIRING_FILE_PATTERN = "_wiring.txt";
const std::string DemonstrationWorkflow::TRELLIS_FILE_PATTERN = "_trellis.txt";
const std::string DemonstrationWorkflow::CLEAN_DECODED_FILE_PATTERN = "_decoded.txt";
const std::string DemonstrationWorkflow::NOISY_DECODED_FILE_PATTERN = "_decoded_noisy.txt";

/**
 * @brief Demonstrates all features of the coursework.
 * @param p Encoder wiring permutation
 * @param inputData Original input data
 * @param filenameBase Base filename for output files
 * @param out Output stream to print information to
 *
 * Workflow steps are:
 * - permutation generation
 * - clean encoding
 * - trellis generation
 * - clean decode
 * - error injection
 * - noisy decode
 * - clean & noisy decode compariosn to input data
 */
void DemonstrationWorkflow::RunWorkflow(Permutation p, BitStream inputData,
                                        std::string filenameBase, std::ostream &out,
                                        std::mutex &outMutex)
{
  // Create base encoder
  Encoder_ptr encoder = std::make_shared<Encoder>();
  encoder->addComponent(std::make_shared<XORGate>("xor1"));
  encoder->addComponent(std::make_shared<XORGate>("xor2"));
  encoder->addComponent(std::make_shared<RegisterArray>("r", 4));
  encoder->attachWire("input_bus.bit_0", "r.bit_0");

  // Get and apply permutation to encoder
  p.apply(encoder);

  // Perform validation
  if (!encoder->validate())
  {
    std::lock_guard<std::mutex> guard(outMutex);
    out << "Permutation failed to generate valid wiring.\n";
    return;
  }

  if (!encoder->validateComponentUse())
  {
    std::lock_guard<std::mutex> guard(outMutex);
    out << "Permutation failed to use all components.\n";
    return;
  }

  // Encode
  std::vector<bool> cleanEncodedData;
  cleanEncodedData.reserve(inputData.size() * 2);
  encoder->encode(inputData, cleanEncodedData);
  BinaryFileIO::WriteFile(cleanEncodedData, filenameBase + CLEAN_ENCODED_FILE_PATTERN);

  // Output wiring info
  std::ofstream wiringOut;
  wiringOut.open(filenameBase + WIRING_FILE_PATTERN, std::fstream::out);
  wiringOut << *encoder << '\n';
  wiringOut.close();

  // Generate trellis
  Trellis trellis = encoder->generateTrellis();
  std::ofstream trellisOut;
  trellisOut.open(filenameBase + TRELLIS_FILE_PATTERN, std::fstream::out);
  trellisOut << trellis << '\n';
  trellisOut.close();

  Decoder decoder(trellis);

  // Decode
  std::vector<bool> cleanDecodedData;
  cleanDecodedData.reserve(inputData.size());
  size_t cleanDecoderHammingDist = decoder.decode(cleanEncodedData, cleanDecodedData);
  BinaryFileIO::WriteFile(cleanDecodedData, filenameBase + CLEAN_DECODED_FILE_PATTERN);

  // Inject error
  std::vector<bool> noisyEncodedData;
  noisyEncodedData.reserve(cleanEncodedData.size());
  ErrorInjector::InjectError(cleanEncodedData, noisyEncodedData);
  BinaryFileIO::WriteFile(noisyEncodedData, filenameBase + NOISY_ENCODED_FILE_PATTERN);

  // Decode with error
  std::vector<bool> noisyDecodedData;
  noisyDecodedData.reserve(inputData.size());
  size_t noisyDecoderHammingDist = decoder.decode(noisyEncodedData, noisyDecodedData);
  BinaryFileIO::WriteFile(noisyDecodedData, filenameBase + NOISY_DECODED_FILE_PATTERN);

  // Compare
  size_t cleanDecodedDataHammingDist = BitStreamComparator::Compare(inputData, cleanDecodedData);
  size_t noisyDecodedDataHammingDist = BitStreamComparator::Compare(inputData, noisyDecodedData);

  // Output results
  {
    std::lock_guard<std::mutex> guard(outMutex);
    out << filenameBase << "\nClean decode hamming distance = " << cleanDecodedDataHammingDist
        << " (" << cleanDecoderHammingDist << ")\n"
        << "Noisy decode hamming distance = " << noisyDecodedDataHammingDist << " ("
        << noisyDecoderHammingDist << ")\n\n";
  }
}

/**
 * @brief Creates a new workflow job scheduler.
 * @param out Output stream to print info to
 * @param inputData Input data to process
 */
DemonstrationWorkflow::DemonstrationWorkflow(std::ostream &out,
                                             const CircuitSimulator::BitStream &inputData)
    : m_out(out)
    , m_outMutex()
    , m_inputData(inputData)
{
}

DemonstrationWorkflow::~DemonstrationWorkflow()
{
  join();
}

/**
 * @brief Adds a new workflow job to the scheduler and starts it executing.
 * @param p Permutation to use in this job
 * @param filenameBase Base filename to save output to
 */
void DemonstrationWorkflow::addJob(Permutation p, std::string filenameBase)
{
  m_threads.push_back(std::thread(RunWorkflow, p, m_inputData, filenameBase, std::ref(m_out),
                                  std::ref(m_outMutex)));
}

/**
 * @brief Joins all threads that are still running.
 */
void DemonstrationWorkflow::join()
{
  for (auto it = m_threads.begin(); it != m_threads.end(); ++it)
  {
    if (it->joinable())
      it->join();
  }
}
}