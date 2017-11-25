#include "Level.h"

Level::Level()
{
}

Level::~Level()
{
}

void Level::loadLevel(string fileName, Player &player)
{
	ifstream levelFile;
	string levelLine;

	//Loading Level File
	levelFile.open(fileName);

	if (levelFile.fail())
	{
		perror(fileName.c_str());
		system("PAUSE");
		exit(1);
	}

	while (getline(levelFile, levelLine))
	{
		_levelData.push_back(levelLine);
	}

	levelFile.close();
	//Level File Loaded

	//Processing Level File
	char unitTile;

	for (int i = 0; i < _levelData.size(); ++i)
	{
		for (int j = 0; j < _levelData[i].size(); ++j)
		{
			unitTile = _levelData[i][j];

			switch (unitTile)
			{
				case '@': player.setPosition(j, i); //Player
					break;

				case 'M': _enemies.push_back(Enemy("Monster", unitTile, 50, 30, 50, 40, 3));
					_enemies.back().setPosition(j, i);
					break;

				case 'G': _enemies.push_back(Enemy("Gargoyle", unitTile, 40, 50, 20, 35, 2));
					_enemies.back().setPosition(j, i);
					break;

				case 'D': _enemies.push_back(Enemy("Dragon", unitTile, 100, 100, 100, 100, 10));
					_enemies.back().setPosition(j, i);
					break;

				case 'S': _enemies.push_back(Enemy("Skeleton", unitTile, 10, 5, 5, 5, 1));
					_enemies.back().setPosition(j, i);
					break;
			}
		}
	}
}

void Level::displayLevel()
{
	system("cls");

	for (int i = 0; i < _levelData.size(); ++i)
	{
		printf("%s", _levelData[i].c_str());
		printf("\n");
	}
}

void Level::movePlayer(char move, Player &player)
{
	/*char previousUnitUp;
	char previousUnitDown;
	char previousUnitRight;
	char previousUnitLeft;*/
	int playerX;
	int playerY;

	player.getPosition(playerX, playerY);

	/*previousUnitUp = _levelData[playerY - 1][playerX];
	previousUnitDown = _levelData[playerY + 1][playerX];
	previousUnitLeft = _levelData[playerY][playerX - 1];
	previousUnitRight = _levelData[playerY][playerX + 1];*/

	switch (move)
	{
		//Up
		case 'w':
		case 'W': movePlayerLogic(player, playerX, playerY - 1);
			break;

		//Left
		case 'a':
		case 'A': movePlayerLogic(player, playerX - 1, playerY);
			break;

		//Down
		case 's':
		case 'S': movePlayerLogic(player, playerX, playerY + 1);
			break;

		//Right
		case 'd':
		case 'D': movePlayerLogic(player, playerX + 1, playerY);
			break;

		default: printf("\nInvalid Input!!\n");
			system("PAUSE");
			break;
	}
}

void Level::movePlayerLogic(Player &player, int moveX, int moveY)
{
	int playerX;
	int playerY;
	char input;

	player.getPosition(playerX, playerY);

	char moveToUnit = getUnitTile(moveX, moveY);

	switch (moveToUnit)
	{
		case '.': /*previousUnitUp = _levelData[playerY - 1][playerX];*/
			player.setPosition(moveX, moveY);
			setUnitTile(playerX, playerY, '.');
			setUnitTile(moveX, moveY, '@');
			break;

		case 'D':
		case 'G':
		case 'M':
		case 'S': battleEnemy(player, moveX, moveY);
			break;

		case '#': //printf("\nYou hit a wall!!\n");
			//system("PAUSE>NULL");
			break;

		case '~': player.setPosition(moveX, moveY);
			setUnitTile(playerX, playerY, '~');
			setUnitTile(moveX, moveY, '@');
			break;

		case '?': player.unknownEncounter();
			player.setPosition(moveX, moveY);
			setUnitTile(playerX, playerY, '.');
			setUnitTile(moveX, moveY, '@');
			break;

		case '>': printf("\nConsole...>> Load next level?\nConsole (Y/N): ");
			input = _getch();

			if ((input == 'Y') || (input == 'y'))
			{
				clearLevel();
				_levelPath.push_back("Levels\\Level_" + to_string(++_levelCounter) + ".level");
				loadLevel(_levelPath.back(), player);
			}

		case 'x':
			break;

		default:
			break;
	}
}

char Level::getUnitTile(int x, int y)
{
	return _levelData[y][x];
}

void Level::setUnitTile(int x, int y, char unitTile)
{
	_levelData[y][x] = unitTile;
}

void Level::battleEnemy(Player &player, int targetX, int targetY)
{
	int enemyX;
	int enemyY;
	int playerX;
	int playerY;
	int attackPower;
	int attackResult;

	for (int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i].getPosition(enemyX, enemyY);

		if ((targetX == enemyX) && (targetY == enemyY))
		{
			//Battle
			attackPower = player.attackChance();
			attackResult = _enemies[i].takeDamage(attackPower);
			printf("\nPlayer attacked %s with %d damage!!, %s's health: %d", _enemies[i].getEnemyName().c_str(), attackPower, _enemies[i].getEnemyName().c_str(), _enemies[i].getEnemyHealth());
			system("PAUSE>null");

			if (attackResult > 0)
			{
				player.addXP(attackResult);
				setUnitTile(targetX, targetY, '.');
				displayLevel();
				printf("\n%s died!!!", _enemies[i].getEnemyName().c_str());
				//remove enemy
				_enemies[i] = _enemies.back();
				_enemies.pop_back();
				--i;
				system("PAUSE>null");

				return;
			}

			//Enemy Turn
			attackPower = _enemies[i].attackChance();
			attackResult = player.takeDamage(attackPower);
			printf("\n%s attacked Player with %d damage!!, Player's health: %d", _enemies[i].getEnemyName().c_str(), attackPower, player.getPlayerHealth());
			system("PAUSE>null");

			if (attackResult != 0)
			{
				player.getPosition(playerX, playerY);
				setUnitTile(playerX, playerY, 'X');
				displayLevel();
				printf("\nYou died!!!");
				system("PAUSE>null");

				exit(0);
			}

			return;
		}
	}
}

void Level::updateEnemyPosition(Player &player)
{
	char aiMove;
	int playerX;
	int playerY;
	int enemyX;
	int enemyY;

	player.getPosition(playerX, playerY);

	for (int i = 0; i < _enemies.size(); ++i)
	{
		aiMove = _enemies[i].getMove(playerX,playerY);
		_enemies[i].getPosition(enemyX, enemyY);

		switch (aiMove)
		{
			//Up
			case 'w':
				moveEnemyLogic(player, i, enemyX, enemyY - 1);
				break;

			//Left
			case 'a':
				moveEnemyLogic(player, i, enemyX - 1, enemyY);
				break;

			//Down
			case 's':
				moveEnemyLogic(player, i, enemyX, enemyY + 1);
				break;

			//Right
			case 'd':
				moveEnemyLogic(player, i, enemyX + 1, enemyY);
				break;
		}
	}
}

void Level::moveEnemyLogic(Player &player, int enemyIndex, int moveX, int moveY)
{
	int playerX;
	int playerY;
	int enemyX;
	int enemyY;

	_enemies[enemyIndex].getPosition(enemyX, enemyY);

	char moveToUnit = getUnitTile(moveX, moveY);

	switch (moveToUnit)
	{
		case '.': /*previousUnitUp = _levelData[playerY - 1][playerX];*/
			_enemies[enemyIndex].setPosition(moveX, moveY);
			setUnitTile(enemyX, enemyY, '.');
			setUnitTile(moveX, moveY, _enemies[enemyIndex].getChar());
			break;

		case '@': battleEnemy(player, enemyX, enemyY);
			break;

		default:
			break;
	}
}

void Level::clearLevel()
{
	_levelData.clear();
	_enemies.clear();
}

void Level::saveProgress(int levelNum, int x, int y)
{
	ofstream saveToFile;
}