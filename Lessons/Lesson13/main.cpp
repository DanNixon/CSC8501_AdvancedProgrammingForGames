#include <iostream>
#include <string>
#include <vector>

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

  std::vector<int> scores(5, 0);

  scores[0] = 1;
  scores[1] = 2;
  scores[2] = 3;

  for (int i = 0; i < scores.size(); ++i)
    std::cout << "scores " << i << " = " << scores[i] << "\n";

  std::vector<Enemy> *enemies = new std::vector<Enemy>(3);

  Enemy fourth, fifth;

  enemies->push_back(fourth);
  enemies->push_back(fifth);
  std::cout << "size of enemies = " << enemies->size() << "\n";

  int i = 0;
  for (auto it = enemies->begin(); it != enemies->end(); ++it)
  {
    it->set_score(scores[i]);
    std::cout << "score = " << it->get_score() << "\n";
    ++i;
  }

  Enemy newthird;
  enemies->insert(enemies->begin() + 2, newthird);
  enemies->erase(enemies->begin() + 2);

  Enemy &back = enemies->back();
  std::cout << "hit points last element = " << back.get_hit_points() << "\n";

  enemies->pop_back();
  std::cout << "new size of enemies = " << enemies->size() << "\n";

  enemies->clear();

  delete enemies;

  return 0;
}
