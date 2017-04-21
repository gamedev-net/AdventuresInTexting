#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <memory>
#include <algorithm>

using namespace std;

vector<string> split(const string& str) {
    string buf; // Have a buffer string
    stringstream ss(str); // Insert the string into a stream
    vector<string> tokens; // Create vector to hold our words

    while (ss >> buf)
        tokens.push_back(buf);

    return tokens;
}

struct Map
{
    enum Location
    {
        GRAVEYARD,
        GRAVEYARD_GATES,
        KHATHARRS_MOMS_HOUSE,
    };
	Location map_location[100][100];
	int x, y;
	Map()
	{
		x = 50;
		y = 50;
		map_location[50][50] = GRAVEYARD;
		map_location[50][51] = GRAVEYARD_GATES;
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

struct Player : public Entity
{
    Player(string name, int health) : Entity(name, health) {}

    virtual bool act(vector<string> commands) override
    {
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
                break;
            case Map::KHATHARRS_MOMS_HOUSE:
                break;
        }

        cout << "Can't travel " << direction << endl;
        return false;
    }

    void look()
    {
        switch (map.map_location[map.x][map.y])
        {
            case Map::GRAVEYARD:
                cout << "A thick layer of fog covers the graveyard soil. Tombstones jut out here and there and an eerie willow tree looms over your head, obstructing the full moon partially. Off in the distance you see the northern gates -- the only entrance into this forsaken place." << endl;
                break;
            case Map::GRAVEYARD_GATES:
                cout << "For many centuries these gates have stood the test of time. The gateway to the afterlife. Inside the graveyard small hills stretch endlessly, littered with thousands of tombstones. You see a willow tree south of the gates." << endl;
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

    void useItem(int index)
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
