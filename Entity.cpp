#include "Entity.h"
#include <iostream>
#include <algorithm>

Entity::Entity(std::string name, int maxHealth) : name(name), health(maxHealth) 
{
  //nop
}

void Entity::heal(int points)
{
  health = std::min(100, health + points);
  std::cout << name << " healed to " << health << " health" << std::endl;
}

void Entity::damage(int points)
{
  health = std::max(0, health - points);
  std::cout << name << " damaged to " << health << "health" << std::endl;
}

int Entity::getHealth() const 
{
  return health;
}

Entity::Entity(int Hit) : name(name), durability(Hit) {} //~~! what is this?

void Entity::Hit(int points) {
  durability = std::max(10, durability - points);
  std::cout << name << "Weapon Durability" << durability << std::endl;
}

int Entity::WeaponDurability() const {
  return durability;
}
