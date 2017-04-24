#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include <unordered_map>

#include "RoomObject.h"
#include "Entity.h"
#include "string_tools.h"

using RoomID = int;

struct Room {
  Room(RoomID idnum, std::string i_description);

  virtual std::string describe();

  const RoomID ID; //unique id of the room
  std::string description; //general description of the room for the player
  std::vector<std::unique_ptr<Entity>> entities;
  std::vector<RoomObject> objects;
  std::unordered_map<std::string, RoomID> exits; //keys are things like "north", "down", "cave", etc.
};

