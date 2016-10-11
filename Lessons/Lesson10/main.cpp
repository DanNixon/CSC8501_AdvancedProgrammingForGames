#include <iostream>

// declare enemy class

class Enemy
{
public:
  Enemy(int hps);
  virtual ~Enemy();
  virtual int get_hit_points() const;
  virtual int get_score() const;
  virtual void set_hit_points(int new_hit_points);
  virtual void set_score(int new_score);

protected:
  int hit_points;
  int *score;
};

// define enemy class

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

// declare flying enemy class

class ArmedEnemy : public Enemy
{
public:
  ArmedEnemy(int hps, int ammo);
  virtual ~ArmedEnemy();
  virtual void set_score(const int new_score);
  virtual void shoot();

protected:
  int ammo_level;
};

// define flying enemy class

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

  delete ae;
  ae = NULL;
  return 0;
}
