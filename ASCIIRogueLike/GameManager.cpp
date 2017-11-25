#include "GameManager.h"


GameManager::GameManager(string levelFileName)
{
	_player.init(100, 10, 10, 0, 1);
	_level.loadLevel(levelFileName, _player);
	//_level.displayLevel();
}

GameManager::~GameManager()
{
}

void GameManager::runGame()
{
	int input = 3;
	bool gameOver = false;

	/*while ((input == 3) || (input == 4))
	{
		switch (input)
		{
			case 1: 
				break;

			case 2: 
				break;

			case 3: system("cls");

				break;

			case 4: system("cls");
				break;

			default:
				break;
		}
	}*/

	while (!gameOver)
	{
		_level.displayLevel();
		playerInput();
		_level.updateEnemyPosition(_player);
	}
}

void GameManager::playerInput()
{
	char input;
	printf("\nConsole.. (w/a/s/d)>> ");
	input = _getch();
	_level.movePlayer(input, _player);
}

void GameManager::mainMenu()
{
	for (int i = 0; i < _mainMenu.size(); i++)
	{
		printf("%s\n", _mainMenu[i].c_str());
	}

	system("PAUSE>null");
}