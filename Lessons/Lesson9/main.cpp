#include <iostream>

class Enemy
{
public:
  Enemy(int hps);
  ~Enemy();
  int get_hit_points() const;
  int get_score() const;
  void set_hit_points(int new_hit_points);
  void set_score(int new_score);

private:
  int hit_points;
  int *score;
};

Enemy::Enemy(int hps)
    : hit_points(hps)
{
  score = new int(0);
}

Enemy::~Enemy()
{
  delete score;
}

int Enemy::get_hit_points() const
{
  return hit_points;
}

int Enemy::get_score() const
{
  return *score;
}

void Enemy::set_hit_points(const int new_hit_points)
{
  hit_points = new_hit_points;
}

void Enemy::set_score(const int new_score)
{
  *score = new_score;
}

int main(void)
{

  Enemy e1(2);
  cout << "hit points = " << e1.get_hit_points() << "\n";

  Enemy *e2 = new Enemy(2);
  e2->set_hit_points(3);
  cout << "hit points = " << e2->get_hit_points() << "\n";

  e2->set_score(2);
  cout << "score = " << e2->get_score() << "\n";

  delete e2;
  e2 = NULL;
  return 0;
}
