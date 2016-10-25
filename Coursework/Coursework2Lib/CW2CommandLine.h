/** @file */

#pragma once

#include "CommandLineInterfaceLib/CLI.h"

namespace Coursework2
{
class CW2CommandLine : public CommandLineInterface::CLI
{
public:
  CW2CommandLine(std::istream &in, std::ostream &out);
  virtual ~CW2CommandLine();

  void initCLI();
};
}