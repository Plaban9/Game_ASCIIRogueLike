#include "Player.h"

Player::Player()
{
}


Player::~Player()
{
}

void Player::init(int health, int attack, int defence, int xp, int level)
{
	_health = health;
	_attack = attack;
	_defence = defence;
	_xp = xp;
	_level = level;
}

void Player::getPosition(int &x, int &y)
{
	x = _x;
	y = _y;
}

void Player::setPosition(int x, int y)
{
	_x = x;
	_y = y;
}

int Player::attackChance()
{
	static mt19937 randomEngine(time(NULL));
	uniform_int_distribution<int> attackPower(0, _attack);

	return attackPower(randomEngine);
}

int Player::takeDamage(int attackChance)
{
	attackChance -= _defence;

	//if attack does damage after defence
	if (attackChance > 0)
	{
		_health -= attackChance;

		if (_health <= 0)
			return 1;
	}

	return 0;
}

void Player::addXP(int xp)
{
	_xp += xp;
	
	printf("\nXP gained: %d", xp);
	printf("\nTotal XP: %d", _xp);
	system("PAUSE>null");

	while (_xp >= _xpThreshlod) //Level_UP
	{
		_xpThreshlod += _xpThreshlod;
		_attack += 0.7 * _attack;
		_defence += 0.7 * _defence;
		_health += 0.7 * _health;
		++_level;

		printf("\nLevel UP!!");
		printf("\nLevel Reached: %d", _level);
		printf("\nPress ENTER to continue...");
		system("PAUSE>null");
	}
}

int Player::getPlayerHealth()
{
	return _health;
}

void Player::unknownEncounter()
{
	static mt19937 randomEngine(time(NULL));
	uniform_int_distribution<int> bonusChance(0, 3);

	switch (bonusChance(randomEngine))
	{
		case 0: printf("\nBonus XP: +20 XP");
			addXP(20);
			system("PAUSE>null");
			break;

		case 1: printf("\nAttack: +20");
			_attack += 20;
			system("PAUSE>null");
			break;

		case 2: printf("\nDefence: +20");
			_defence += 20;
			system("PAUSE>null");
			break;

		case 3: printf("\nHealth: +20");
			_health += 20;
			system("PAUSE>null");
			break;
	}
}