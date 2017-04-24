#pragma once
#include <memory>

#include "Room.h"
#include "Map.h"
#include "declared_entities.h"
#include "declared_items.h"

struct Graveyard : public Room
{
  Graveyard() : Room(Map::Location::GRAVEYARD, "A thick layer of fog covers the graveyard soil. Tombstones jut out here and there and an eerie willow tree looms over your head, obstructing the full moon partially. Off in the distance you see the northern gates -- the only entrance into this forsaken place.") 
  {
    exits["north"] = Map::Location::GRAVEYARD_GATES;
  }
};

struct GraveyardGates : public Room
{
  GraveyardGates() : Room(Map::Location::GRAVEYARD_GATES, "For many centuries these gates have stood the test of time. The gateway to the afterlife. Inside the graveyard small hills stretch endlessly, littered with thousands of tombstones. You see a willow tree south of the gates. Outisde, north, you see a very large house.")
  {
    exits["north"] = Map::Location::KHATHARRS_MOMS_HOUSE;
    exits["south"] = Map::Location::GRAVEYARD;
  }
};

struct KhatharrsMomsHouse : public Room
{
  KhatharrsMomsHouse() : Room(Map::Location::KHATHARRS_MOMS_HOUSE, "The house is gigantic! What could possibly require such volume, such mass, such density? The house appears to not have any doors, but due to the strain from whatever is present inside, cracks have formed. You see a crack you might just fit into.")
  {
    exits["south"] = Map::Location::GRAVEYARD_GATES;
    exits["east"] = Map::Location::GATES_OF_SHOGUN;
  }
};

struct GatesOfShogun : public Room
{
  GatesOfShogun() : Room(Map::Location::GATES_OF_SHOGUN, "Here lies the Gates of the Great Shogun. Creator of A1 weaponry; able to fork stakes by a mere glare. It is said that to look into his eyes is to see your future covered in darkness. As you notice the thick red stains which cover the gates, you are reminded of the villagers' tales of sacrifices hung from these very gates. The gate has no lock. Do you enter?")
  {
    exits["west"] = Map::Location::KHATHARRS_MOMS_HOUSE;
    exits["east"] = Map::Location::HOUSE_OF_BLUES;
    exits["south"] = Map::Location::FOGGY_FOREST;
    entities.emplace_back(std::make_unique<Shogun>());
  }
};

struct FoggyForest : public Room
{
  FoggyForest() : Room(Map::Location::FOGGY_FOREST, "Not much is known about this forest. Only that a wolf howls 3 times in the night, every night. And those who enter have never been known to return. Do you risk your life for adventure?")
  {
    exits["north"] = Map::Location::GATES_OF_SHOGUN;
  }
};

struct HouseOfBlues : public Room
{
  HouseOfBlues() : Room(Map::Location::HOUSE_OF_BLUES, "This is a place where men shed tears and pour out emotion! Of course, after 2 or 3 pints of the finest ale. The miscreants who frequent cavernous house know the warmth of beds not their own. Doors sing with laughter and a timely cry or two. Will you enter to find love?")
  {
    exits["west"] = Map::Location::GATES_OF_SHOGUN;
  }
};

struct HouseOfGDNet : public Room
{
  HouseOfGDNet() : Room(Map::Location::HOUSE_OF_GDNET, "Where else would you want to be?")
  {
    exits["up"] = Map::Location::FOGGY_FOREST;
    entities.push_back(std::make_unique<Khawk>());
    entities.push_back(std::make_unique<MyopicRhino>());
  }
};