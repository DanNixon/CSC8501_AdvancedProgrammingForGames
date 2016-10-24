/** @file */

#include "CW2CommandLine.h"

#include "CommandLineInterfaceLib/SubCommand.h"
#include "UtilityLib/BinaryFileIO.h"

using namespace CommandLineInterface;
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
      "compare",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        // TODO
        out << "TODO\n";
        return COMMAND_EXIT_CLEAN;
      },
      3, "Compares two or more data files to check for similarity."));

  registerCommand(std::make_shared<Command>(
      "inject_error",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        // TODO
        out << "TODO\n";
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