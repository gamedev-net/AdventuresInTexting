#pragma once
#include <string>
#include <vector>

struct Entity
{
  Entity(std::string name, int maxHealth) ;

  void heal(int points);

  void damage(int points);

  int getHealth() const;

  Entity(int Hit); //~~! what is this?

  void Hit(int points);

  int WeaponDurability() const;

  // Return false if the entity didn't know the command
  virtual bool act(std::vector<std::string> commands) = 0;

  std::string name;

private:
  int health;
  int durability;

};

