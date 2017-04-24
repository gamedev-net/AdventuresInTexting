#pragma once
#include <vector>
#include <string>
#include <limits>

#include "Entity.h"

struct Shogun : public Entity
{
  Shogun() : Entity("Shogibear", 100) 
  {
    //nop
  }

  bool act(std::vector<std::string> commands) {
    return false;
  }

};

struct Khawk : public Entity
{
  Khawk() : Entity("Khawk", std::numeric_limits<int>::max())
  {
    //nop
  }

  bool act(std::vector<std::string> commands) {
    return false;
  }

};

struct MyopicRhino : public Entity
{
  MyopicRhino(): Entity("Nearsighted One", std::numeric_limits<int>::max())
  {
    //nop
  }

  bool act(std::vector<std::string> commands) 
  {
    return false;
  }

};