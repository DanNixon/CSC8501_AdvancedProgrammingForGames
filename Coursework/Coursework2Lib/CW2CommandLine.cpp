/** @file */

#include "CW2CommandLine.h"

#include "CommandLineInterfaceLib/SubCommand.h"
#include "Coursework1Lib/BitStreamComparator.h"
#include "Coursework2Lib/ErrorInjector.h"
#include "UtilityLib/BinaryFileIO.h"

using namespace CommandLineInterface;
using namespace CircuitSimulator;
using namespace Utility;
using namespace Coursework1;

namespace Coursework2
{
/**
 * @brief Create a new command line on given streams.
 * @param in Input stream
 * @param out Output stream
 */
CW2CommandLine::CW2CommandLine(std::istream &in, std::ostream &out)
    : CLI(in, out)
{
}

CW2CommandLine::~CW2CommandLine()
{
}

/**
 * @brief Add commands to the CLI.
 */
void CW2CommandLine::initCLI()
{
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
        // TODO
        return COMMAND_EXIT_CLEAN;
      },
      3, "Decodes encoded data."));

  registerCommand(std::make_shared<Command>(
      "compare",
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
}
}
