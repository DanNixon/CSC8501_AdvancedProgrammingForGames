#pragma once

#include "Enemy.h"

class ArmedEnemy : public Enemy
{
public:
  static const int default_ammo = 8;

  ArmedEnemy()
      : Enemy()
      , ammo_level(default_ammo)
  {
  }

  ArmedEnemy(int hps, int ammo)
      : Enemy(hps)
      , ammo_level(ammo)
  {
  }

  virtual ~ArmedEnemy()
  {
  }

  virtual void set_score(int new_score);
  virtual void shoot();

protected:
  int ammo_level;
};