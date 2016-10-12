#pragma once

class Comparable
{
public:
  virtual int compare_to(const Comparable &other) = 0;
};