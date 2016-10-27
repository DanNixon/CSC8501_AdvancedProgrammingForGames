/** @file */

#pragma once

#include <string>
#include <vector>

namespace CircuitSimulator
{
/**
 * @brief Stores one mapping within a Trellis.
 */
struct TrellisMapping
{
  size_t srcState;  //!< Source/current state index
  bool bit;         //!< Corresponding data bit
  std::string code; //!< Mapped code segment
  size_t destState; //!< Destination/next state index

  size_t tempCost; //!< Holds a cost used in decoding algorithm
};

/**
 * @class Trellis
 * @author Dan Nixon
 * @brief Stores a trellis mapping for decoding.
 */
class Trellis
{
public:
  static Trellis LoadFromFile(const std::string &filename);

public:
  Trellis(const std::vector<TrellisMapping> &mapping = {});
  virtual ~Trellis();

  /**
   * @brief Returns the number of unique states in the trellis.
   * @return State count
   */
  inline size_t numStates() const
  {
    return m_numStates;
  }

  /**
   * @brief Gets the number of mappings in this trellis.
   * @return Mappings count
   */
  inline size_t numMappings() const
  {
    return m_mapping.size();
  }

  /**
   * @brief Gets a mapping given its index.
   * @param i Mapping index
   * @return Maping
   */
  TrellisMapping mapping(size_t i) const
  {
    return m_mapping[i];
  }

  void getMappingsForDestinationState(std::vector<TrellisMapping> &mappings,
                                      size_t destStateIdx) const;

  friend std::ostream &operator<<(std::ostream &stream, const Trellis &o);
  friend std::istream &operator>>(std::istream &stream, Trellis &o);

private:
  void cacheStateCount();

private:
  size_t m_numStates;
  std::vector<TrellisMapping> m_mapping;
};
}
