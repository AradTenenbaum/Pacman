#include <iostream>
#include "Game.h"
#include <cassert>
#include <conio.h>
#include <windows.h>
#include "utils.h"
#include <cstdlib>

using namespace std;

int main()
{
	srand((unsigned)time(NULL));

	Game game = Game();
	game.startMenu();

    return 0;
}