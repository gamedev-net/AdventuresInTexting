#include "Adventure.h"

#include <string>
#include <iostream>
#include <memory>

#include "Player.h"
#include "declared_actions.h"
#include "declared_items.h"
#include "string_tools.h"

void Adventure::begin()
{
  std::string command;
  std::cout << "Welcome, brave soul. Pray tell, what is thy name?" << std::endl;
  std::cout << "> ";
  std::getline(std::cin, command);

  Player player(command, 100);
  player.registerAction("smack", smack);
  player.registerAction("look", look);
  player.registerAction("move", doMove);
  player.registerAction("go", doMove);
  player.addItem(std::make_shared<HealthItem>(20));
  player.addItem(std::make_shared<BlessedSword>(10));

  std::cout << player.name << "! Your presence defiles these sacred grounds. Beware the soil upon which you step, for it will claim you sooner rather than later." << std::endl;
  player.look();

  while(player.getHealth() > 0)
  {
    std::cout << "> ";
    std::getline(std::cin, command);
    if(player.act(split(command)) == false)
      std::cout << "Unknown command" << std::endl;
  }

  std::cout << "You died. Game over." << std::endl;
}
