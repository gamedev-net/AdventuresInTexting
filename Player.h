#pragma once
#include <string>
#include <functional>
#include <memory>
#include <unordered_map>

#include "Entity.h"
#include "Map.h"

struct Item;

struct Player : public Entity
{
  Player(std::string name, int health);

  void registerAction(std::string actionName, std::function<bool(Player& player, std::vector<std::string>)> actionFunction);

  bool act(std::vector<std::string> commands) override;
  bool travel(std::string direction);
  void look();

  bool addItem(std::shared_ptr<Item> item);
  void showItems();
  void useItem(size_t index);
  void dropItem(size_t index);

  RoomID currentLocation;

private:
  static const size_t max_inventory_size = 100;
  std::vector<std::shared_ptr<Item>> inventory;
  std::unordered_map<std::string, std::function<bool(Player&, std::vector<std::string>)>> actions;

  Map map;

};

