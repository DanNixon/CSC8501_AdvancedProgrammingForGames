#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "ArmedEnemy.h"
#include "Enemy.h"

class CA
{
public:
  std::string val;
};

class CB
{
public:
  size_t val;
};

int main(void)
{
#if 0
  // auto v2;

  auto v1 = new CA();
  v1->val = "Hello, World!";
  std::cout << v1->val << '\n';

  // v1 = new CB();
#endif

  std::vector<ArmedEnemy> enemies;
  enemies.push_back(ArmedEnemy(20, 100));
  enemies.push_back(ArmedEnemy(90, 100));
  enemies.push_back(ArmedEnemy(10, 100));
  enemies.push_back(ArmedEnemy(40, 100));
  enemies.push_back(ArmedEnemy(70, 100));
  enemies.push_back(ArmedEnemy(100, 100));
  enemies.push_back(ArmedEnemy(30, 100));
  enemies.push_back(ArmedEnemy(80, 100));

  std::sort(enemies.begin(), enemies.end(), [](ArmedEnemy &a, ArmedEnemy &b)
            {
              return a.get_hit_points() < b.get_hit_points();
            });

  for (auto it = enemies.begin(); it != enemies.end(); ++it)
    std::cout << it->get_hit_points() << '\n';

  return 0;
}
