/** @file */

#include "CWCommandLine.h"

#include <algorithm>
#include <fstream>
#include <sstream>

#include "CircuitSimulatorLib/ComponentFactory.h"
#include "CircuitSimulatorLib/RegisterArray.h"
#include "CircuitSimulatorLib/Wire.h"
#include "CircuitSimulatorLib/XORGate.h"
#include "CommandLineInterfaceLib/Command.h"
#include "CourseworkLib/BitStreamComparator.h"
#include "CourseworkLib/Decoder.h"
#include "CourseworkLib/ErrorInjector.h"
#include "UtilityLib/BinaryFileIO.h"
#include "UtilityLib/FileUtils.h"

#include "BitStreamComparator.h"

using namespace CommandLineInterface;
using namespace CircuitSimulator;
using namespace Utility;

namespace Coursework
{
const std::string CWCommandLine::CLEAN_ENCODED_FILE_PATTERN = "_encoded.txt";
const std::string CWCommandLine::NOISY_ENCODED_FILE_PATTERN = "_encoded_noisy.txt";
const std::string CWCommandLine::WIRING_FILE_PATTERN = "_wiring.txt";
const std::string CWCommandLine::TRELLIS_FILE_PATTERN = "_trellis.txt";
const std::string CWCommandLine::CLEAN_DECODED_FILE_PATTERN = "_decoded.txt";
const std::string CWCommandLine::NOISY_DECODED_FILE_PATTERN = "_decoded_noisy.txt";

/**
 * @brief Create a new command line on given streams.
 * @param in Input stream
 * @param out Output stream
 */
CWCommandLine::CWCommandLine(std::istream &in, std::ostream &out)
    : CLI(in, out)
    , m_activeEncoder(std::make_shared<Encoder>())
    , m_permutationGenerator(nullptr)
{
}

CWCommandLine::~CWCommandLine()
{
}

/**
 * @brief Adds commands to the CLI.
 */
void CWCommandLine::initCLI()
{
  SubCommand_ptr encoderCmd = std::make_shared<SubCommand>("encoder", "Configures encoder.");
  encoderCmd->registerCommand(generateComponentCmd());
  encoderCmd->registerCommand(generateWireCmd());
  encoderCmd->registerCommand(generatePermutationCmd());
  encoderCmd->registerCommand(generatePresetCmd());

  encoderCmd->registerCommand(std::make_shared<Command>(
      "reset",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        this->m_activeEncoder = std::make_shared<Encoder>();
        return COMMAND_EXIT_CLEAN;
      },
      1, "Resets the state of the encoder."));

  encoderCmd->registerCommand(std::make_shared<Command>(
      "show",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        out << *(this->m_activeEncoder) << '\n';
        return COMMAND_EXIT_CLEAN;
      },
      1, "Outputs the encoder configuration."));

  registerCommand(encoderCmd);

  registerCommand(std::make_shared<Command>(
      "encode",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        std::vector<bool> dataIn;
        std::vector<bool> dataOut;

        BinaryFileIO::ReadFile(dataIn, argv[1]);
        dataOut.reserve(dataIn.size() * 2);

        this->m_activeEncoder->encode(dataIn, dataOut);

        BinaryFileIO::WriteFile(dataOut, argv[2]);

        return COMMAND_EXIT_CLEAN;
      },
      3, "Encodes data from a file."));

  registerCommand(std::make_shared<Command>(
      "compare",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        if (argv.size() == 3)
        {
          size_t hammingDist = BitStreamComparator::Compare(argv[1], argv[2]);
          out << "Hamming distance: " << hammingDist << '\n';
        }
        else
        {
          std::vector<std::string> filenames(argv.begin() + 1, argv.end());
          if (BitStreamComparator::CompareMultiple(filenames))
            out << "All files match.\n";
          else
            out << "Files differ.\n";
        }
        return COMMAND_EXIT_CLEAN;
      },
      3, "Compares two or more data files to check for similarity."));

  registerCommand(std::make_shared<Command>(
      "find_matching",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        std::vector<std::string> filenames;
        FileUtils::FindFiles(filenames, argv[1], argv[2]);

        BitStreamComparator::IndexListList results;
        BitStreamComparator::FindSimilar(results, filenames);
        if (!results.empty())
        {
          out << "Matching groups:\n";
          size_t i = 0;
          for (auto rIt = results.begin(); rIt != results.end(); ++rIt)
          {
            out << (char)('a' + (i++)) << ": ";
            for (auto gIt = rIt->begin(); gIt != rIt->end(); ++gIt)
              out << *gIt << ' ';
            out << '\n';
          }
        }
        return COMMAND_EXIT_CLEAN;
      },
      3, "Finds matching datasets from files in a directory."));

  registerCommand(std::make_shared<Command>(
      "inject_error",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        BitStream inData;
        BitStream outData;

        BinaryFileIO::ReadFile(inData, argv[1]);
        outData.reserve(inData.size());

        ErrorInjector::InjectError(inData, outData);
        BinaryFileIO::WriteFile(outData, argv[2]);

        return COMMAND_EXIT_CLEAN;
      },
      3, "Injects erronous data into a file."));

  registerCommand(std::make_shared<Command>(
      "decode",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        // Load decoder
        Trellis trellis = Trellis::LoadFromFile(argv[1]);
        Decoder decoder(trellis);

        // Read input data
        BitStream inData;
        BinaryFileIO::ReadFile(inData, argv[2]);

        // Decode
        BitStream outData;
        size_t bestPathMetric = decoder.decode(inData, outData);
        out << "Decoding complete. Best path has weight: " << bestPathMetric << '\n';

        // Save output
        BinaryFileIO::WriteFile(outData, argv[3]);

        return COMMAND_EXIT_CLEAN;
      },
      4, "Decodes encoded data."));

  registerCommand(std::make_shared<Command>(
      "compare_decoded",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        BitStream original;
        BitStream cleanDecode;
        BitStream noisyDecode;

        BinaryFileIO::ReadFile(original, argv[1]);
        BinaryFileIO::ReadFile(cleanDecode, argv[2]);
        BinaryFileIO::ReadFile(noisyDecode, argv[3]);

        out << "Clean decode "
            << (BitStreamComparator::Compare(original, cleanDecode) ? "matches" : "differs")
            << ".\n";
        out << "Noisy decode "
            << (BitStreamComparator::Compare(original, noisyDecode) ? "matches" : "differs")
            << ".\n";

        return COMMAND_EXIT_CLEAN;
      },
      4, "Comapres decoded datasets to original."));

  registerCommand(std::make_shared<Command>(
      "thebigworkflow",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) -> int {
        // Ensure permutations have been generated
        if (this->m_permutationGenerator == nullptr)
        {
          out << "No permutations (try running generate first).\n";
          return 1;
        }

        // Input data
        const std::string workingDirectory(argv[2]);
        std::vector<bool> inputData;
        BinaryFileIO::ReadFile(inputData, argv[1]);

        for (size_t i = 0; i < this->m_permutationGenerator->numPermutations(); i++)
        {
          out << "=== Permutation " << i << '\n';

          // Reset encoder
          this->loadPreset("cw_basic");

          // Get and apply permutation to encoder
          Permutation p = this->m_permutationGenerator->permutation(i);
          p.apply(this->m_activeEncoder);

          // Perform validation
          if (!this->m_activeEncoder->validate())
          {
            out << "Permutation " << i << " failed to generate valid wiring.\n";
            continue;
          }

          if (!this->m_activeEncoder->validateComponentUse())
          {
            out << "Permutation " << i << " failed to use all components.\n";
            continue;
          }

          // Encode
          std::vector<bool> cleanEncodedData;
          cleanEncodedData.reserve(inputData.size() * 2);
          this->m_activeEncoder->encode(inputData, cleanEncodedData);
          BinaryFileIO::WriteFile(cleanEncodedData, workingDirectory + std::to_string(i) +
                                                        CLEAN_ENCODED_FILE_PATTERN);

          // Output wiring info
          std::ofstream wiringOut;
          wiringOut.open(workingDirectory + std::to_string(i) + WIRING_FILE_PATTERN,
                         std::fstream::out);
          wiringOut << *(this->m_activeEncoder) << '\n';
          wiringOut.close();

          // Generate trellis
          Trellis trellis = this->m_activeEncoder->generateTrellis();
          std::ofstream trellisOut;
          trellisOut.open(workingDirectory + std::to_string(i) + TRELLIS_FILE_PATTERN,
                          std::fstream::out);
          trellisOut << trellis << '\n';
          trellisOut.close();

          Decoder decoder(trellis);

          // Decode
          std::vector<bool> cleanDecodedData;
          cleanDecodedData.reserve(inputData.size());
          size_t cleanDecoderHammingDist = decoder.decode(cleanEncodedData, cleanDecodedData);
          BinaryFileIO::WriteFile(cleanDecodedData, workingDirectory + std::to_string(i) +
                                                        CLEAN_DECODED_FILE_PATTERN);

          // Inject error
          std::vector<bool> noisyEncodedData;
          noisyEncodedData.reserve(cleanEncodedData.size());
          ErrorInjector::InjectError(cleanEncodedData, noisyEncodedData);
          BinaryFileIO::WriteFile(noisyEncodedData, workingDirectory + std::to_string(i) +
                                                        NOISY_ENCODED_FILE_PATTERN);

          // Decode with error
          std::vector<bool> noisyDecodedData;
          noisyDecodedData.reserve(inputData.size());
          size_t noisyDecoderHammingDist = decoder.decode(noisyEncodedData, noisyDecodedData);
          BinaryFileIO::WriteFile(noisyDecodedData, workingDirectory + std::to_string(i) +
                                                        NOISY_DECODED_FILE_PATTERN);

          // Compare
          size_t cleanDecodedDataHammingDist =
              BitStreamComparator::Compare(inputData, cleanDecodedData);
          size_t noisyDecodedDataHammingDist =
              BitStreamComparator::Compare(inputData, noisyDecodedData);

          out << "Clean decode hamming distance = " << cleanDecodedDataHammingDist << " ("
              << cleanDecoderHammingDist << ")\n"
              << "Noisy decode hamming distance = " << noisyDecodedDataHammingDist << " ("
              << noisyDecoderHammingDist << ")\n";
        }

        return COMMAND_EXIT_CLEAN;
      },
      3, "Performs encoding, trellis generation, decoding, error injection, decoding and "
         "comnparisons."));
}

/**
 * @brief Genertes commands for the components subcommend.
 * @return Subcommand
 */
SubCommand_ptr CWCommandLine::generateComponentCmd()
{
  SubCommand_ptr cmd = std::make_shared<SubCommand>("components", "Manage encoder components.");

  cmd->registerCommand(std::make_shared<Command>(
      "list",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) -> int {
        auto cIt = std::find_if(this->m_activeEncoder->componentsBegin(),
                                this->m_activeEncoder->componentsEnd(),
                                [&argv](Component_ptr c) { return c->id() == argv[1]; });
        if (cIt == this->m_activeEncoder->componentsEnd())
          return 1;

        for (auto pIt = (*cIt)->pinsBegin(); pIt != (*cIt)->pinsEnd(); ++pIt)
          out << ((*pIt)->isInput() ? 'I' : ' ') << ((*pIt)->isOutput() ? 'O' : ' ') << ": "
              << (*pIt)->id() << '\n';
        return COMMAND_EXIT_CLEAN;
      },
      2, "Lists component pins."));

  cmd->registerCommand(std::make_shared<Command>(
      "add",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        std::vector<std::string> args(argv.begin() + 3, argv.end());
        Component_ptr c = ComponentFactory::Create(argv[1], argv[2], args);
        this->m_activeEncoder->addComponent(c);
        return COMMAND_EXIT_CLEAN;
      },
      3, "Adds a component to the encoder."));

  cmd->registerCommand(std::make_shared<Command>(
      "remove",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) -> int {
        return this->m_activeEncoder->removeComponent(argv[1]) ? COMMAND_EXIT_CLEAN : 1;
      },
      2, "Removes a component from the encoder."));

  return cmd;
}

/**
 * @brief Genertes commands for the wires subcommend.
 * @return Subcommand
 */
SubCommand_ptr CWCommandLine::generateWireCmd()
{
  SubCommand_ptr cmd = std::make_shared<SubCommand>("wires", "Manage encoder wiring.");

  cmd->registerCommand(std::make_shared<Command>(
      "add",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        this->m_activeEncoder->attachWire(argv[1], argv[2]);
        return COMMAND_EXIT_CLEAN;
      },
      3, "Adds a wire between two pins."));

  cmd->registerCommand(std::make_shared<Command>(
      "remove",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        this->m_activeEncoder->removeWire(argv[1], argv[2]);
        return COMMAND_EXIT_CLEAN;
      },
      1, "Removes a wire between two pins."));

  return cmd;
}

/**
 * @brief Genertes commands for the permutations subcommend.
 * @return Subcommand
 */
SubCommand_ptr CWCommandLine::generatePermutationCmd()
{
  SubCommand_ptr cmd =
      std::make_shared<SubCommand>("permutations", "Work with encoder permutations.");

  cmd->registerCommand(std::make_shared<Command>(
      "generate",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        if (this->m_permutationGenerator != nullptr)
          delete this->m_permutationGenerator;

        PermutationGenerator::WireEndpointList endpoints = {
            {{"input_bus.bit_0", "r.bit_1", "r.bit_2", "r.bit_3"},
             {"xor1.a", "xor1.b", "xor2.a", "xor2.b"}},
            {{"xor2.z", "xor1.z"}, {"output_bus.bit_0", "output_bus.bit_1"}}};

        this->m_permutationGenerator = new PermutationGenerator(endpoints);
        this->m_permutationGenerator->generate();

        out << "Generated " << this->m_permutationGenerator->numPermutations()
            << " permutations.\n";
        return COMMAND_EXIT_CLEAN;
      },
      1, "Generates permutations."));

  cmd->registerCommand(std::make_shared<Command>(
      "list",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) -> int {
        if (this->m_permutationGenerator == nullptr)
        {
          out << "No permutations (try running generate first).\n";
          return 1;
        }

        for (size_t i = 0; i < this->m_permutationGenerator->numPermutations(); i++)
          out << i << ' ' << this->m_permutationGenerator->permutation(i) << '\n';

        return COMMAND_EXIT_CLEAN;
      },
      1, "Lists all permutations."));

  cmd->registerCommand(std::make_shared<Command>(
      "load",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) -> int {
        if (this->m_permutationGenerator == nullptr)
        {
          out << "No permutations (try running generate first).";
          return 1;
        }

        Permutation p = this->m_permutationGenerator->permutation(std::stoi(argv[1]));
        p.apply(this->m_activeEncoder);

        return COMMAND_EXIT_CLEAN;
      },
      2, "Loads a permutation into the active encoder."));

  return cmd;
}

/**
 * @brief Genertes commands for the presets subcommend.
 * @return Subcommand
 */
SubCommand_ptr CWCommandLine::generatePresetCmd()
{
  SubCommand_ptr cmd = std::make_shared<SubCommand>("preset", "Load encoder presets.");

  cmd->registerCommand(std::make_shared<Command>(
      "cw_basic",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        this->loadPreset("cw_basic");
        return COMMAND_EXIT_CLEAN;
      },
      1, "Minimal wiring configuration form coursework spec."));

  cmd->registerCommand(std::make_shared<Command>(
      "cw_example",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        this->loadPreset("cw_example");
        return COMMAND_EXIT_CLEAN;
      },
      1, "Minimal wiring configuration form coursework spec."));

  return cmd;
}

/**
 * @brief Handles loading of a preset.
 * @param preset String ID of the preset
 */
void CWCommandLine::loadPreset(const std::string &preset)
{
  this->m_activeEncoder = std::make_shared<Encoder>();

  if (preset == "cw_basic")
  {
    this->m_activeEncoder->addComponent(std::make_shared<XORGate>("xor1"));
    this->m_activeEncoder->addComponent(std::make_shared<XORGate>("xor2"));
    this->m_activeEncoder->addComponent(std::make_shared<RegisterArray>("r", 4));

    this->m_activeEncoder->attachWire("input_bus.bit_0", "r.bit_0");
  }
  else if (preset == "cw_example")
  {
    this->m_activeEncoder->addComponent(std::make_shared<XORGate>("xor1"));
    this->m_activeEncoder->addComponent(std::make_shared<XORGate>("xor2"));
    this->m_activeEncoder->addComponent(std::make_shared<RegisterArray>("r", 4));

    this->m_activeEncoder->attachWire("input_bus.bit_0", "r.bit_0");
    this->m_activeEncoder->attachWire("input_bus.bit_0", "xor2.a");
    this->m_activeEncoder->attachWire("r.bit_1", "xor2.b");
    this->m_activeEncoder->attachWire("xor2.z", "output_bus.bit_0");
    this->m_activeEncoder->attachWire("r.bit_2", "xor1.a");
    this->m_activeEncoder->attachWire("r.bit_3", "xor1.b");
    this->m_activeEncoder->attachWire("xor1.z", "output_bus.bit_1");
  }
  else
    throw std::runtime_error("Preset \"" + preset + "\" not found.");
}
}
