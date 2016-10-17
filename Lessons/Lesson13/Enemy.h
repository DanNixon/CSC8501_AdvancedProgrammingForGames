#pragma once

#include <iostream>

class Enemy
{
public:
  static const int default_hps = 4;
  Enemy()
      : hit_points(default_hps)
  {
    score = new int(0);
  }

  Enemy(int hps)
      : hit_points(hps)
  {
    score = new int(0);
  }

  Enemy(const Enemy &src);
  Enemy &operator=(const Enemy &rhs);

  virtual ~Enemy()
  {
    delete score;
  }

  virtual int get_hit_points() const
  {
    return hit_points;
  }

  virtual int get_score() const
  {
    return *score;
  }

  virtual void set_hit_points(int new_hit_points)
  {
    hit_points = new_hit_points;
  }

  virtual void set_score(int new_score)
  {
    *score = new_score;
  }

protected:
  int hit_points;
  int *score;
};