/** @file */

#include "EncoderMetrics.h"

#include <sstream>

using namespace CircuitSimulator;

namespace Coursework1
{
void EncoderMetrics::GenerateRandomData(BitStream &out, size_t len)
{
  out.reserve(len);

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

  resetStats();

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

    m_stats[posStr.str()][nextStr.str()]++;
  }

  for (auto it = m_stats.begin(); it != m_stats.end(); ++it)
  {
    double sum = it->second["00"] + it->second["01"] + it->second["10"] + it->second["11"];
    it->second["00"] /= sum;
    it->second["01"] /= sum;
    it->second["10"] /= sum;
    it->second["11"] /= sum;
  }
}

void EncoderMetrics::resetStats()
{
  m_stats.clear();

  for (std::string v : {"000", "001", "010", "011", "100", "101", "110", "111"})
  {
    m_stats[v] = {{"00", 0}, {"01", 0}, {"10", 0}, {"11", 0}};
  }
}

std::ostream &operator<<(std::ostream &stream, const EncoderMetrics &o)
{
  for (auto it = o.m_stats.cbegin(); it != o.m_stats.cend(); ++it)
  {
    stream << it->first << '\n';
    for (auto iit = it->second.cbegin(); iit != it->second.cend(); ++iit)
    {
      stream << ' ' << iit->first << " (" << iit->second << ")\n";
    }
  }

  return stream;
}
}