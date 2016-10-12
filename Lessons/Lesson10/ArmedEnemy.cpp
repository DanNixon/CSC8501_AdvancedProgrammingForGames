#include "ArmedEnemy.h"

#include <iostream>

ArmedEnemy::ArmedEnemy(int hps, int ammo)
    : Enemy(hps)
    , ammo_level(ammo)
{
}

ArmedEnemy::~ArmedEnemy()
{
}

void ArmedEnemy::set_score(const int new_score)
{
  *score = new_score;
  std::cout << "score is now " << *score << "\n";
}

void ArmedEnemy::shoot()
{
  if (ammo_level > 0)
  {
    std::cout << "bang!\n";
    --ammo_level;
  }
  else
  {
    std::cout << "out of ammo\n";
  }
}
