#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <memory>
#include <algorithm>
#include <cstring>
#include <unordered_map>
#include <functional>

using namespace std;

vector<string> split(const string& str) {
    string buf; // Have a buffer string
    stringstream ss(str); // Insert the string into a stream
    vector<string> tokens; // Create vector to hold our words

    while (ss >> buf)
        tokens.push_back(buf);

    return tokens;
}

using RoomID = int;

struct RoomObject
{
	vector<string> names;
	string description;
	bool visible;
};

struct Room;

struct Map
{
	static const int max_width = 100, max_height = 100;
	static const int player_start_x = 50, player_start_y = 50;
    enum Location
    {
		UNKNOWN,
		GRAVEYARD,
		GRAVEYARD_GATES,
		KHATHARRS_MOMS_HOUSE,
		GATES_OF_SHOGUN,
		HOUSE_OF_BLUES,
		FOGGY_FOREST
    };
	Location map_location[max_width][max_height];
	int x, y;
	Map()
	{
        memset(map_location, UNKNOWN, sizeof(map_location));
		x = 50;
		y = 50;
		/*map_location[50][50] = GRAVEYARD;
		map_location[50][51] = GRAVEYARD_GATES;
		map_location[50][52] = KHATHARRS_MOMS_HOUSE;
		map_location[50][52] = GATES_OF_SHOGUN;
		map_location[50][53] = HOUSE_OF_BLUES;
		map_location[50][54] = FOGGY_FOREST;*/
	}

  unordered_map<RoomID, unique_ptr<Room>> rooms;
};

struct Entity
{
    Entity(string name, int maxHealth) : name(name), health(maxHealth) {}

    void heal(int points)
    {
        health = min(100, health + points);
        cout << name << " healed to " << health << " health" << endl;
    }

    void damage(int points)
    {
        health = max(0, health - points);
        cout << name << " damaged to " << health << "health" << endl;
    }

    int getHealth() const { return health; }

    // Return false if the entity didn't know the command
    virtual bool act(vector<string> commands) = 0;

    string name;
    //Map map;

private:
    int health;
};

struct Shogun : public Entity {
  Shogun() : Entity("Shogibear", 100) {}
};

struct Item
{
    virtual void apply(Entity* entity) = 0;
    virtual string identify() const = 0;
};

struct HealthItem : public Item
{
    HealthItem(int healPower) : healPower(healPower) {}

    void apply(Entity* entity) override
    {
        entity->heal(healPower);
    }

    string identify() const override
    {
        stringstream ss;
        ss << "Health Potion (" << healPower << ")";
        return ss.str();
    }

private:
    int healPower;
};
struct BlessedSword : public Item
{
    BlessedSword(int Weapon) : Weapon(Weapon){}
void apply(Entity* entity) override{entity->damage(Weapon);}string identify() const override{stringstream ss; ss << "Hit (" << Weapon << ")";}
private: int Weapon;};//will add this to entity on my next commit. <.<

/*
struct ReallyFastSword : public Item
struct TheFastcall : public Entity
{
    TheFastcall() : Entity("The Fastcall", 22) {}
    virtual bool act(vector<string> commands) override
    {
    }
};
*/


struct Room {
    Room(RoomID idnum, string i_description) : ID(idnum) {
        description = i_description;
    }
    virtual string describe() {
        stringstream ss;
        ss << description << "\n";
        ss << "Entities: "; for (auto& ent : entities) { ss << ent->name << ", "; }; ss << "\n"; //make this look nice later
        ss << "Items: "; for (auto& obj : objects) { ss << obj.names[0] << ", "; }; ss << "\n";  //make this look nice later
        ss << "Obvious exits: "; for (auto kv : exits) { ss << kv.first << ", "; } ss << "\n"; //...
        return ss.str();
    }
    const RoomID ID; //unique id of the room
    string description; //general description of the room for the player
    vector<unique_ptr<Entity>> entities;
    vector<RoomObject> objects;
    unordered_map<string, RoomID> exits; //keys are things like "north", "down", "cave", etc.
};

struct Graveyard : public Room
{
    Graveyard() : Room(Map::Location::GRAVEYARD, "The graveyard") {}
};

typedef bool (*actionHandlerBYEBYENAMECOLLISION)(vector<string> commands); // unused, but we can't technically delete this, and commenting it out is just cheating.

struct Player : public Entity
{
    Player(string name, int health) : Entity(name, health) 
    {
        map.rooms[Map::Location::GRAVEYARD] = unique_ptr<Room>(new Room(Map::Location::GRAVEYARD, "Graveyard description"));
        map.rooms[Map::Location::GRAVEYARD_GATES] = unique_ptr<Room>(new Room(Map::Location::GRAVEYARD, "Graveyard gates description"));
        map.rooms[Map::Location::KHATHARRS_MOMS_HOUSE] = unique_ptr<Room>(new Room(Map::Location::GRAVEYARD, "Moms house"));
        map.rooms[Map::Location::GATES_OF_SHOGUN] = unique_ptr<Room>(new Room(Map::Location::GRAVEYARD, "Gates of shogun"));
        map.rooms[Map::Location::HOUSE_OF_BLUES] = unique_ptr<Room>(new Room(Map::Location::GRAVEYARD, "Blues"));
        map.rooms[Map::Location::FOGGY_FOREST] = unique_ptr<Room>(new Room(Map::Location::GRAVEYARD, "Forest"));
    }

    bool act(vector<string> commands) override
    {
        auto cmd = commands[0];
        if(cmd == "n") { commands = vector<string>{"go","north"}; }
        if(cmd == "s") { commands = vector<string>{"go","south"}; }
        if(cmd == "e") { commands = vector<string>{"go","east"}; }
        if(cmd == "w") { commands = vector<string>{"go","west"}; }

        if (commands.size() >= 1 && commands[0] == "look")
        {
            look();
            return true;
        }
        else if (commands.size() >= 2 && (commands[0] == "examine" || commands[0] == "x"))
        {
        }
        else if (commands.size() >= 2 && commands[0] == "go")
        {
            if (travel(commands[1]) == true)
            {
                look();
            } else {
                cout << "Can't travel " << commands[1] << endl;
            }
            return true;
        }
        else if (commands.size() >= 1 && commands[0] == "items")
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

        return false;
    }

    bool travel(string direction)
    {
		if ((map.x <= 0 && direction == "west") || (map.x >= (map.max_width - 1) && direction == "east"))
			return false;
		if ((map.y <= 0 && direction == "south") || (map.y >= (map.max_width - 1) && direction == "north"))
			return false;
		if ((direction == "north"&&map.map_location[map.x][map.y + 1] == Map::UNKNOWN) || (direction == "south"&&map.map_location[map.x][map.y - 1] == Map::UNKNOWN) || (direction == "east"&&map.map_location[map.x + 1][map.y] == Map::UNKNOWN)||(direction=="west"&&map.map_location[map.x-1][map.y]==Map::UNKNOWN))return false;
		if (direction == "north")map.y++; if (direction == "south")map.y--; if (direction == "east")map.x++; if (direction == "west")map.x--;
        return true;/*
        switch (map.map_location[map.x][map.y])
        {
            case Map::GRAVEYARD:
                if (direction == "north")
                {
					map.y++;
                    return true;
                }
                break;
            case Map::GRAVEYARD_GATES:
                if (direction == "south")
                {
					map.y--;
                    return true;
                }
                if (direction == "north")
                {
                    map.y++;
                    return true;
                }
                break;
        }

        cout << "Can't travel " << direction << endl;
        return false;*/
    }

    void look()
    {
        switch (map.map_location[map.x][map.y])
        {
            case Map::GRAVEYARD:
                cout << "A thick layer of fog covers the graveyard soil. Tombstones jut out here and there and an eerie willow tree looms over your head, obstructing the full moon partially. Off in the distance you see the northern gates -- the only entrance into this forsaken place." << endl;
                break;
            case Map::GRAVEYARD_GATES:
                cout << "For many centuries these gates have stood the test of time. The gateway to the afterlife. Inside the graveyard small hills stretch endlessly, littered with thousands of tombstones. You see a willow tree south of the gates. Outisde, north, you see a very large house." << endl;
                break;
            case Map::KHATHARRS_MOMS_HOUSE:
                cout << "The house is gigantic! What could possibly require such volume, such mass, such density? The house appears to not have any doors, but due to the strain from whatever is present inside, cracks have formed. You see a crack you might just fit into east." << endl;
                break;
			case Map::GATES_OF_SHOGUN:
				cout << "Here lies the Gates of the Great Shogun. Creator of A1 weaponry; able to fork stakes by a mere glare. It is said that to look into his eyes is to see your future covered in darkness. As you notice the thick red stains which cover the gates, you are reminded of the villagers' tales of sacrifices hung from these very gates. The gate has no lock. Do you enter?" << endl;
				break;
			case Map::HOUSE_OF_BLUES:
				cout << "This is a place where men shed tears and pour out emotion! Of course, after 2 or 3 pints of the finest ale. The miscreants who frequent cavernous house know the warmth of beds not their own. Doors sing with laughter and a timely cry or two. Will you enter to find love?" << endl;
				break;
			case Map::FOGGY_FOREST:
				cout << "Not much is known about this forest. Only that a wolf howls 3 times in the night, every night. And those who enter have never been known to return. Do you risk your life for adventure?" << endl;
				break;
        }
    }

    void giveItem(shared_ptr<Item> item)
    {
        inventory.push_back(item);
    }

    void showItems()
    {
        if (inventory.size() == 0)
            cout << "You have no items." << endl;
        int i = 1;
        for (auto item : inventory)
        {
            cout << "  " << i++ << ". " << item->identify() << std::endl;
        }
    }

    void useItem(size_t index)
    {
        if (index > inventory.size())
        {
            cout << "Invalid index" << endl;
            return;
        }

        inventory[index-1]->apply(this);
        inventory.erase(inventory.begin() + index - 1);
    }

    RoomID currentLocation;

private:
    vector<shared_ptr<Item>> inventory;
    unordered_map<string, function<bool(vector<string>)>> actions;

    Map map;
};


class Adventure
{
public:
    void begin()
    {
        string command;
        cout << "Welcome, brave soul. Pray tell, what is thy name?" << endl;
        cout << "> ";
        getline(cin, command);

        Player player(command, 100);
        player.giveItem(make_shared<HealthItem>(20));

        cout << player.name << "! Your presence defiles these sacred grounds. Beware the soil upon which you step, for it will claim you sooner rather than later." << endl;
        player.look();

        while (player.getHealth() > 0)
        {
            cout << "> ";
            getline(cin, command);
            if (player.act(split(command)) == false)
                cout << "Unknown command" << endl;
        }

        cout << "You died. Game over." << endl;
    }
};

int main()
{
    Adventure adventure;
    adventure.begin();
    return 0;
}
