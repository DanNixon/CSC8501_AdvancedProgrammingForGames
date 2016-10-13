#pragma once

class Item
{
public:
  inline void setValue(int value)
  {
    m_value = value;
  }

  inline int getValue() const
  {
    return m_value;
  }

private:
  int m_value;
};