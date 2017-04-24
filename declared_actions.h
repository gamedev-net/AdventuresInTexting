#pragma once
#include "Player.h"

bool smack(Player& p, std::vector<std::string> commands)
{
  if(commands.size() >= 2)
  {
    std::cout << "You smack " << commands[1] << " with righteous indignation!" << std::endl;
    return true;
  }
  else {
    return false;
  }

}

bool look(Player& player, std::vector<std::string> commands)
{
  player.look();
  return true;
}

bool doMove(Player& player, std::vector<std::string> commands)
{
  if(commands.size() < 2)
  {
    std::cout << "Can't travel " << commands[1] << std::endl;
    return false;
  }
  player.travel(commands[1]); return true;
}
