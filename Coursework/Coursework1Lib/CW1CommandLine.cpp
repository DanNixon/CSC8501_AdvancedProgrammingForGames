/** @file */

#include "CW1CommandLine.h"

#include <algorithm>
#include <fstream>
#include <sstream>

#include "CircuitSimulatorLib/ComponentFactory.h"
#include "CircuitSimulatorLib/RegisterArray.h"
#include "CircuitSimulatorLib/Wire.h"
#include "CircuitSimulatorLib/XORGate.h"
#include "CommandLineInterfaceLib/Command.h"
#include "UtilityLib/BinaryFileIO.h"
#include "UtilityLib/FileUtils.h"

#include "BitStreamComparator.h"
#include "EncoderMetrics.h"

using namespace CommandLineInterface;
using namespace CircuitSimulator;
using namespace Utility;

namespace Coursework1
{
/**
 * @brief Create a new command line on given streams.
 * @param in Input stream
 * @param out Output stream
 */
CW1CommandLine::CW1CommandLine(std::istream &in, std::ostream &out)
    : CLI(in, out)
    , m_activeEncoder(std::make_shared<Encoder>())
    , m_permutationGenerator(nullptr)
{
}

CW1CommandLine::~CW1CommandLine()
{
}

/**
 * @brief Adds commands to the CLI.
 */
void CW1CommandLine::initCLI()
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

  encoderCmd->registerCommand(std::make_shared<Command>(
      "metrics",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        EncoderMetrics m(this->m_activeEncoder);
        BitStream data;
        EncoderMetrics::GenerateRandomData(data, 500);
        m.measure(data);
        out << m;
        return COMMAND_EXIT_CLEAN;
      },
      1, "Shows metrics of state changes with random input data."));

  SubCommand_ptr encodeCmd = std::make_shared<SubCommand>("encode", "Performs encoding.");

  encodeCmd->registerCommand(std::make_shared<Command>(
      "string",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        std::stringstream inStr(argv[1]);

        std::vector<bool> dataIn;
        std::vector<bool> dataOut;

        BinaryFileIO::Read(dataIn, inStr);
        dataOut.reserve(dataIn.size() * 2);

        this->m_activeEncoder->encode(dataIn, dataOut);

        for (auto it = dataOut.begin(); it != dataOut.end(); ++it)
          out << (*it);
        out << "\n";

        return COMMAND_EXIT_CLEAN;
      },
      2, "Encodes a string."));

  encodeCmd->registerCommand(std::make_shared<Command>(
      "file",
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

  encodeCmd->registerCommand(std::make_shared<Command>(
      "cw1workflow",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) -> int {
        if (this->m_permutationGenerator == nullptr)
        {
          out << "No permutations (try running generate first).\n";
          return 1;
        }

        std::vector<bool> dataIn;
        BinaryFileIO::ReadFile(dataIn, argv[1]);

        for (size_t i = 0; i < this->m_permutationGenerator->numPermutations(); i++)
        {
          // Reset encoder
          this->loadPreset("cw_basic");

          std::vector<bool> dataOut;
          dataOut.reserve(dataIn.size() * 2);

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

          // Perform encoding
          this->m_activeEncoder->encode(dataIn, dataOut);

          // Output wiring info
          std::string wiringFilename = argv[2] + "enc_" + std::to_string(i) + "_wiring.txt";
          std::ofstream wiringOut;
          wiringOut.open(wiringFilename, std::fstream::out);
          wiringOut << *(this->m_activeEncoder) << '\n';
          wiringOut.close();

          // Calculate and output metrics
          EncoderMetrics metrics(this->m_activeEncoder);
          metrics.measure(dataIn);
          std::string metricsFilename = argv[2] + "enc_" + std::to_string(i) + "_metrics.txt";
          std::ofstream metricsOut;
          metricsOut.open(metricsFilename, std::fstream::out);
          metricsOut << metrics << '\n';
          metricsOut.close();

          // Save encoded string
          std::string outFilename = argv[2] + "enc_" + std::to_string(i) + "_out.txt";
          BinaryFileIO::WriteFile(dataOut, outFilename);

          out << "Permutation " << i << " saved to: " << outFilename << '\n';
        }

        return COMMAND_EXIT_CLEAN;
      },
      3, "Performs permutation generation and encoding steps for coursework 1."));

  registerCommand(encoderCmd);
  registerCommand(encodeCmd);

  registerCommand(std::make_shared<Command>(
      "compare",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        std::vector<std::string> filenames(argv.begin() + 1, argv.end());
        if (BitStreamComparator::CompareMultiple(filenames))
          out << "All files match.\n";
        else
          out << (filenames.size() > 2 ? "Some f" : "F") << "iles differ.\n";
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
}

/**
 * @brief Genertes commands for the components subcommend.
 * @return Subcommand
 */
SubCommand_ptr CW1CommandLine::generateComponentCmd()
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
SubCommand_ptr CW1CommandLine::generateWireCmd()
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
SubCommand_ptr CW1CommandLine::generatePermutationCmd()
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
SubCommand_ptr CW1CommandLine::generatePresetCmd()
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
void Coursework1::CW1CommandLine::loadPreset(const std::string &preset)
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
