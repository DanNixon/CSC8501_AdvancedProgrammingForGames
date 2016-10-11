#include <iostream>

#include "Enemy.h"
#include "ArmedEnemy.h"
#include "Boss.h"

void some_function(Enemy &enemy)
{
  enemy.set_score(6);
}

int main(void)
{
  ArmedEnemy *ae = new ArmedEnemy(2, 5);
  ae->set_hit_points(3);
  std::cout << "hit points = " << ae->get_hit_points() << "\n";

  ae->shoot();

  some_function(*ae);

  Boss b(2, 5, 10);
  std::cout << "Boss armour: " << b.get_armour() << '\n';

  b.set_armour(8);
  std::cout << "Boss armour: " << b.get_armour() << '\n';

  delete ae;
  ae = NULL;
  return 0;
}
