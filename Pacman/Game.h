#pragma once

#include "Game.h"
#include "Board.h"
#include "Pacman.h"
#include <string>

using namespace std;

class Game {
	enum { ESC = 27, ENTER = 13,  LIVES = 5 };
	Board gameBoard;
	Pacman player;
	int points=0, lives=LIVES;
public:
	void displayMenu();
	void displayInstructions();
	void init();
	void run();
private:
	bool isValidMove(int dir);
	void setStats();
	void addPoints(int add);
	bool onBreadCurmb();
	void dropLive();
	void pause();
	void draw();
};

