#pragma once

#include "ArmedEnemy.h"

class Boss : public ArmedEnemy
{
public:
  Boss(int hps, int ammo, int armour);
  virtual ~Boss();

  int get_armour() const;
  void set_armour(int armour);

private:
  int armour;
};