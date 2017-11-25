#include "Enemy.h"

Enemy::Enemy(string name, char unitTile, int health, int attack, int defence, int xp, int level)
{
	_name = name;
	_unitTile = unitTile;
	_health = health;
	_attack = attack;
	_defence = defence;
	_xp = xp;
	_level = level;
}

Enemy::~Enemy()
{
}

void Enemy::getPosition(int &x, int &y)
{
	x = _x;
	y = _y;
}

void Enemy::setPosition(int x, int y)
{
	_x = x;
	_y = y;
}

int Enemy::attackChance()
{
	static mt19937 randomEngine(time(NULL));
	uniform_int_distribution<int> attackPower( 0, _attack);

	return attackPower(randomEngine);
}

int Enemy::takeDamage(int attackChance)
{
	attackChance -= _defence;

	//check if attack does damage
	if (attackChance > 0)
	{
		_health -= attackChance;

		//Check if it died
		if (_health <= 0)
			return _xp;
	}

	return 0;
}

string Enemy::getEnemyName()
{
	return _name;
}

int Enemy::getEnemyHealth()
{
	return _health;
}

char Enemy::getChar()
{
	return _unitTile;
}

char Enemy::getMove(int playerX, int playerY)
{
	static mt19937 randomEngine(time(NULL));
	uniform_int_distribution<int> moveRoll(0, 6);

	int distance; //from Player
	int dx = _x - playerX;
	int dy = _y - playerY;
	int adx = abs(dx);
	int ady = abs(dy);
	int randomMove;
	distance = adx + ady;

	if (distance <= 5)
	{
		if (adx > ady) //Moves along x-axis
		{
			if (dx > 0) //Right of player
				return 'a';

			else
				return 'd';
		}

		else
		{
			if (dy > 0) //Right of player
				return 'w';

			else
				return 's';
		}
	}

	randomMove = moveRoll(randomEngine);

	switch (randomMove)
	{
		case 0:
			return 'w';

		case 1:
			return 'a';

		case 2:
			return 's';

		case 3:
			return 'd';

		default:
			return '.';
	}
}