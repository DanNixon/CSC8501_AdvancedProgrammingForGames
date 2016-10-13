#include <iostream>

#include "Enemy.h"
#include "Item.h"
#include "Player.h"

int main(void)
{
#if 1
  Player p1(5, "yuuka");
  std::cout << "P1 HP: " << p1.get_hit_points()
            << "\nP1 name: " << p1.get_name() << '\n';

  p1.set_name("tenshi");
  std::cout << "P1 HP: " << p1.get_hit_points()
            << "\nP1 name: " << p1.get_name() << '\n';

  Enemy e1(2);
  std::cout << "hit points = " << e1.get_hit_points() << '\n';

  Enemy *e2 = new Enemy(2);
  e2->set_hit_points(3);
  std::cout << "hit points = " << e2->get_hit_points() << '\n';

  e2->set_score(2);
  std::cout << "score = " << e2->get_score() << '\n';

  delete e2;
  e2 = NULL;
#endif

#if 0
  //Player p;
  Item i;
  std::cout << "Item value: " << i.getValue() << '\n';
  i.setValue(10);
  std::cout << "Item value: " << i.getValue() << '\n';
#endif

  return 0;
}
