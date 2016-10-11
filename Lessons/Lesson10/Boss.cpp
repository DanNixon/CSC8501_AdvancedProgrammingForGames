#include "Boss.h"

Boss::Boss(int hps, int ammo, int armour)
  : ArmedEnemy(hps, ammo)
  , armour(armour)
{
}

Boss::~Boss()
{
}

int Boss::get_armour() const
{
  return armour;
}

void Boss::set_armour(int armour)
{
  this->armour = armour;
}