#pragma once

#include "Game.h"
#include "Board.h"
#include "Pacman.h"
#include "Ghost.h"
#include <string>

using namespace std;

class Game {
	enum { ESC = 27, ENTER = 13, SPACE = ' ', LIVES = 3 };
	Board gameBoard;
	Pacman player;
	Ghost ghost1;
	Ghost ghost2;
	int points=0, lives=LIVES;
	bool isColors = true;
public:
	void displayMenu();
	void displayInstructions();
	void displaySettings();
	void init();
	void run();
	void setColors() { isColors = !isColors; };
private:
	bool isValidMove(int dir);
	void setStats();
	void addPoints(int add);
	bool onBreadCurmb();
	void dropLive();
	void pause();
	void draw();
	void getPossibleDirs(Position pos, int possibleDirs[]);
};

