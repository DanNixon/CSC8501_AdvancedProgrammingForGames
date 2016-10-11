#pragma once

class Enemy
{
public:
  Enemy(int hps);
  virtual ~Enemy();
  virtual int get_hit_points() const;
  virtual int get_score() const;
  virtual void set_hit_points(int new_hit_points);
  virtual void set_score(const int new_score);

protected:
  int hit_points;
  int *score;
};