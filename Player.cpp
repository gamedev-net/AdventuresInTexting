#include "Player.h"

#include <iostream>

#include "declared_rooms.h"

Player::Player(std::string name, int health) : Entity(name, health) 
{
  currentLocation = Map::Location::GRAVEYARD;
  map.rooms[Map::Location::GRAVEYARD] = std::make_unique<Graveyard>();
  map.rooms[Map::Location::GRAVEYARD_GATES] = std::make_unique<GraveyardGates>();
  map.rooms[Map::Location::KHATHARRS_MOMS_HOUSE] = std::make_unique<KhatharrsMomsHouse>();
  map.rooms[Map::Location::GATES_OF_SHOGUN] = std::make_unique<GatesOfShogun>();
  map.rooms[Map::Location::HOUSE_OF_BLUES] = std::make_unique<HouseOfBlues>();
  map.rooms[Map::Location::FOGGY_FOREST] = std::make_unique<FoggyForest>();
}

void Player::registerAction(std::string actionName, std::function<bool(Player& player, std::vector<std::string>)> actionFunction)
{
  actions[actionName] = actionFunction;
}

bool Player::act(std::vector<std::string> commands)
{
  if(commands.empty()) { return false; }  
  auto cmd = commands[0];
  if(cmd == "n") { commands = std::vector<std::string>{"go","north"}; }
  if(cmd == "s") { commands = std::vector<std::string>{"go","south"}; }
  if(cmd == "e") { commands = std::vector<std::string>{"go","east"}; }
  if(cmd == "w") { commands = std::vector<std::string>{"go","west"}; }

  if (commands.size() >= 1 && commands[0] == "items")
  {
    showItems();
    return true;
  }
  else if (commands.size() >= 2 && commands[0] == "use")
  {
    int index = stoi(commands[1]);
    useItem(index);
    return true;
  }
  else if (commands.size() >= 1 && actions.find(commands[0]) != actions.end())
  {
    return actions[commands[0]](*this, commands);
  }

  return false;
}

bool Player::travel(std::string direction)
{
  if (map.rooms.at(currentLocation)->exits.find(direction) == map.rooms.at(currentLocation)->exits.end())
    return false;
  currentLocation = map.rooms.at(currentLocation)->exits[direction];
  look();
  return true;
}

void Player::look()
{
  std::cout << map.rooms.at(currentLocation)->describe() << std::endl;
}

bool Player::addItem(std::shared_ptr<Item> item)
{
  if (inventory.size() >= max_inventory_size) return false;
  inventory.push_back(item);
  return true;
}

void Player::showItems()
{
  if (inventory.size() == 0)
    std::cout << "You have no items." << std::endl;
  int i = 1;
  for (auto item : inventory)
  {
    std::cout << "  " << i++ << ". " << item->identify() << std::endl;
  }
}

void Player::useItem(size_t index)
{
  if (index > inventory.size())
  {
    std::cout << "Invalid index" << std::endl;
    return;
  }

  inventory[index-1]->apply(this);
  inventory.erase(inventory.begin() + index - 1);
}

void Player::dropItem(size_t index)
{
  if (index > inventory.size())
  {
    std::cout << "Invalid index" << std::endl;
    return;
  }
  inventory.erase(inventory.begin() + index - 1);
}
