#include "ArmedEnemy.h"

void ArmedEnemy::set_score(int new_score)
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