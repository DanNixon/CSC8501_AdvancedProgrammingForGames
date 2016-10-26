/** @file */

#pragma once

#include <string>
#include <vector>

namespace Coursework2
{
  struct TrellisMapping
  {
    size_t srcState;
    bool bit;
    std::string code;
    size_t destState;
  };

  class Trellis
  {
  public:
    static const size_t NUM_STATES;

  public:
    Trellis(const std::vector<TrellisMapping> &mapping = {});
    virtual ~Trellis();

    inline size_t numMappings() const
    {
      return m_mapping.size();
    }

    TrellisMapping mapping(size_t i) const
    {
      return m_mapping[i];
    }

    friend std::ostream &operator<<(std::ostream &stream, const Trellis &o);
    friend std::istream &operator>>(std::istream &stream, Trellis &o);

  private:
    std::vector<TrellisMapping> m_mapping;
  };
}