#include "Room.h"

Room::Room(RoomID idnum, std::string i_description) : ID(idnum)
{
  description = i_description;
}

std::string Room::describe()
{
  std::stringstream ss;
  ss << description << "\n";
  ss << "Entities: "; std::vector<std::string> entNames; for(auto& ent : entities) { entNames.push_back(ent->name); }; ss << listThings(entNames) << "\n";
  ss << "Items: "; std::vector<std::string> objNames; for(auto& obj : objects) { objNames.push_back(obj.names[0]); }; ss << listThings(objNames, true) << "\n";
  ss << "Obvious exits: "; std::vector<std::string> exitNames; for(auto kv : exits) { exitNames.push_back(kv.first); }; ss << listThings(exitNames) << "\n";
  return ss.str();
}
