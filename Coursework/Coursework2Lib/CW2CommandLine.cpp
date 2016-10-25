/** @file */

#include "CW2CommandLine.h"

#include "CommandLineInterfaceLib/SubCommand.h"
#include "Coursework2Lib/ErrorInjector.h"
#include "UtilityLib/BinaryFileIO.h"

using namespace CommandLineInterface;
using namespace CircuitSimulator;
using namespace Utility;

namespace Coursework2
{
CW2CommandLine::CW2CommandLine(std::istream &in, std::ostream &out)
    : CLI(in, out)
{
}

CW2CommandLine::~CW2CommandLine()
{
}

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
        out << "TODO\n";
        return COMMAND_EXIT_CLEAN;
      },
      3, "Decodes encoded data."));
}
}