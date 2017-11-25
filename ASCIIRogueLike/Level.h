#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <cstdio>
#include <conio.h>
#include "Player.h"
#include "Enemy.h"

using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::to_string;

class Level
{
private:
	int _levelCounter = 1;
	vector<string> _levelData;
	vector<Enemy> _enemies;
	vector<string> _levelPath;
	void movePlayerLogic(Player &player, int moveX, int moveY);
	void moveEnemyLogic(Player &player, int enemyIndex, int moveX, int moveY);
	void battleEnemy(Player &player, int targetX, int targetY);

public:
	Level();
	~Level();
	void loadLevel(string fileName, Player &player);
	void displayLevel();
	void movePlayer(char move, Player &player);
	void updateEnemyPosition(Player &player);
	char getUnitTile(int x, int y);
	void setUnitTile(int x, int y, char unitTile);
	void saveProgress(int levelNum, int x, int y);
	void clearLevel();
};