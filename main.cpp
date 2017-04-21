#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <memory>
#include <algorithm>
#include <cstring>
#include <unordered_map>

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
};

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
    };
	Location map_location[max_width][max_height];
	int x, y;
	Map()
	{
        memset(map_location, UNKNOWN, sizeof(map_location));
		x = 50;
		y = 50;
		map_location[50][50] = GRAVEYARD;
		map_location[50][51] = GRAVEYARD_GATES;
		map_location[50][52] = KHATHARRS_MOMS_HOUSE;
	}
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
    Map map;

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
struct TheFastcall : public Entity
{
    TheFastcall() : Entity("The Fastcall", 22) {}
    virtual bool act(vector<string> commands) override
    {
    }
*/

struct Player : public Entity
{
    Player(string name, int health) : Entity(name, health) {}

    virtual bool act(vector<string> commands) override
    {
        auto& cmd = commands[0];
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
        if(direction=="north"&&map.map_location[map.x][map.y+1]==Map::UNKNOWN)return false;if(direction=="south"&&map.map_location[map.x][map.y-1]==Map::UNKNOWN)return false;if(direction=="east"&&map.map_location[map.x+1][map.y]==Map::UNKNOWN)return false
        ;if(direction=="west"&&map.map_location[map.x-1][map.y]==Map::UNKNOWN)return false;if(direction=="north")map.y++;if(direction=="south")map.y--;if(direction=="east")map.x++;if(direction=="west")map.x--;
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

private:
    vector<shared_ptr<Item>> inventory;
};

struct Room {
	string description;
	vector<Entity> entities;
	vector<RoomObject> objects;
	unordered_map<string, RoomID> exits; };

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
