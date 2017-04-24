#pragma once
#include <string>

struct Entity;

struct Item
{
  virtual void apply(Entity* entity) = 0;
  virtual std::string identify() const = 0;
};
