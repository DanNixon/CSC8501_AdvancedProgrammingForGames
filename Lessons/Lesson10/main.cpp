#include <ctime>
#include <iostream>

#include "ArmedEnemy.h"
#include "Boss.h"
#include "Enemy.h"

void hitEnemy(Enemy *e, int hp = 1);

int main(void)
{
  std::srand((unsigned int)std::time(0));

  const size_t NUM_ENEMIES = 11;
  Enemy *enemies[NUM_ENEMIES];

  // Add armed enemies
  for (size_t i = 0; i < NUM_ENEMIES - 1; i++)
    enemies[i] = new ArmedEnemy(100, 20);

  // Add boss
  enemies[NUM_ENEMIES - 1] = new Boss(200, 50, 50);

  long totalHp;
  do
  {
    totalHp = 0;
    for (size_t i = 0; i < NUM_ENEMIES; i++)
    {
      hitEnemy(enemies[i], std::rand() % 20);
      int hp = enemies[i]->get_hit_points();
      std::cout << i << ": hp=" << hp << '\n';
      totalHp += hp;
    }
    std::cout << "===== Total HP = " << totalHp << '\n';
  } while (totalHp > 0);

  return 0;
}

void hitEnemy(Enemy *e, int hp)
{
  int newHp = e->get_hit_points() - hp;
  if (newHp < 0)
    newHp = 0;
  e->set_hit_points(newHp);
}
