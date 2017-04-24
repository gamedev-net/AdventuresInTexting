#pragma once
#include <unordered_map>
#include <memory>
#include "Room.h"


struct Map
{
  enum Location
  {
    UNKNOWN,
    GRAVEYARD,
    GRAVEYARD_GATES,
    KHATHARRS_MOMS_HOUSE,
    GATES_OF_SHOGUN,
    HOUSE_OF_BLUES,
    FOGGY_FOREST,
    HOUSE_OF_GDNET = 999999,
    MAX_LOCATIONS
  };

  std::unordered_map<RoomID, std::unique_ptr<Room>> rooms;
};
