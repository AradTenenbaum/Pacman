#include <iostream>
#include "Game.h"
#include <cassert>
#include <conio.h>
#include <windows.h>
#include "utils.h"

using namespace std;


int main()
{
	Game game = Game();
	int choice;
	bool isPressedExit = false;
	while (!isPressedExit) {
		game.displayMenu();
		cin >> choice;
		if (choice == 1) {
			game.init();
			game.run();
		}
		else if (choice == 8) {
			game.displayInstructions();
		}
		else if (choice == 9) {
			isPressedExit = true;
		}
	}

    return 0;
}