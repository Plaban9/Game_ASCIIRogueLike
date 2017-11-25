#pragma once
#include <random>
#include <ctime>

enum class PlayerStats
{
	XP, ATTACK, DEFENCE, HEALTH
};


using std::mt19937;
using std::uniform_int_distribution;
using std::time;

class Player
{
private:
	//Player Status
	int _health;
	int _attack;
	int _defence;
	int _xp;
	int _level;
	int _xpThreshlod = 5;

	//Player Location
	int _x;
	int _y;

public:
	Player();
	~Player();
	void init(int health, int attack, int defence, int xp, int level);
	void getPosition(int &x, int &y);
	void setPosition(int x, int y);
	int attackChance();
	int takeDamage(int attackChance);
	void addXP(int xp);
	int getPlayerHealth();
	void unknownEncounter();
};