/** @file */

#include "EncoderMetrics.h"

#include <map>
#include <sstream>

using namespace CircuitSimulator;

namespace Coursework1
{
void EncoderMetrics::GenerateRandomData(BitStream &out, size_t len)
{
  for (size_t i = 0; i < len; i++)
    out.push_back((std::rand() % 2) == 0);
}

EncoderMetrics::EncoderMetrics(Encoder_ptr encoder)
    : m_encoder(encoder)
{
}

EncoderMetrics::~EncoderMetrics()
{
}

void EncoderMetrics::measure(const BitStream &data)
{
  BitStream out;
  out.reserve(data.size() * 2);

  m_encoder->encode(data, out);
  m_encoder->resetRegisters();

  std::map<std::string, std::map<std::string, size_t>> resultMap;
  for (std::string v : {"000", "001", "010", "011", "100", "101", "110", "111"})
  {
    resultMap[v] = {{"00", 0}, {"01", 0}, {"10", 0}, {"11", 0}};
  }

  bool last[] = {false, false};
  auto oIt = out.cbegin();
  for (auto it = data.cbegin(); it != data.cend(); ++it)
  {
    std::stringstream posStr;
    posStr << last[0] << last[1] << *it;

    last[0] = *(oIt++);
    last[1] = *(oIt++);

    std::stringstream nextStr;
    nextStr << last[0] << last[1];

    resultMap[posStr.str()][nextStr.str()]++;
  }

  // TODO
}
}