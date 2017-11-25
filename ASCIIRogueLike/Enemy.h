#pragma once

#include <string>
#include <random>
#include <ctime>

using std::string;
using std::mt19937;
using std::uniform_int_distribution;
using std::time;

class Enemy
{
private:
	string _name;
	char _unitTile;

	//Enemy Status
	int _health;
	int _attack;
	int _xp;
	int _defence;
	int _level;

	//Enemy Location
	int _x;
	int _y;

public:
	Enemy(string name, char unitTile, int health, int attack, int defence, int xp, int level);
	~Enemy();
	void getPosition(int &x, int &y);
	void setPosition(int x, int y);
	int attackChance();
	int takeDamage(int attackChance); //return 0 if not dead else return xp
	string getEnemyName();
	int getEnemyHealth();
	char getMove( int playerX, int playerY);
	char getChar();
};