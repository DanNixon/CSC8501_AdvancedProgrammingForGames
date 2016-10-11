#pragma once

#include <string>

class Player
{
public:
  Player(int hps, const std::string & name);
  ~Player();
  int get_hit_points() const;
  int get_score() const;
  std::string get_name() const;
  void set_hit_points(int new_hit_points);
  void set_score(int new_score);
  void set_name(const std::string &name);

private:
  int hit_points;
  int *score;
  std::string *name;
};