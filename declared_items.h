#pragma once
#include <sstream>

#include "Item.h"
#include "Entity.h"

struct HealthItem : public Item
{
  HealthItem(int healPower) : healPower(healPower) {}

  void apply(Entity* entity) override
  {
    entity->heal(healPower);
  }

  std::string identify() const override
  {
    std::stringstream ss;
    ss << "Health Potion (" << healPower << ")";
    return ss.str();
  }

private:
  int healPower;
};

struct BlessedSword : public Item
{
  BlessedSword(int Weapon) : Weapon(Weapon)
  {
  }

  void apply(Entity* entity) override {
    entity->damage(Weapon);
  }

  std::string identify() const override {
    std::stringstream ss;
    ss << "Blessed Sword (" << Weapon << ")";
    return ss.str();
  }

private:
  int Weapon;

};
