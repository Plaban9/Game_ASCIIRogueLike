#include <iostream>
#include <string>
#include <conio.h>

#include "GameManager.h"

#include <windows.h>
#include <filesystem>

// C++ Program to get the current working directory
#include <iostream>   
#include <direct.h>   
using namespace std;


int main()
{
	GameManager gameManger("Levels/Level_1.level");

	gameManger.runGame();

	cout << "\nPress ENTER to continue...\n";
	_getch();
	return 0;
}