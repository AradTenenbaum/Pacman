#pragma once

#include "Game.h"
#include "Board.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Fruit.h"
#include <string>
#include <iostream>
#include <list>

using namespace std;

class Game {
	enum { ESC = 27, ENTER = 13, SPACE = ' ', LIVES = 3 };
	Board gameBoard;
	Pacman* player;
	Ghost ghost1;
	Ghost ghost2;
	list<GameObject*> gameObjects;
	int points=0, lives=LIVES;
	bool isColors = true;
	int speed = 200;
	int maxFruitAmount = 5;
	int maxGhostsAmount = 2;
public:
	void displayMenu();
	void displayInstructions();
	void displaySettings();
	void init();
	void run();
	void setPlayer(Pacman* p) { player = p; };
	void setColors() { isColors = !isColors; };
private:
	bool isValidMove(int dir);
	void setStats();
	void addPoints(int add);
	bool onBreadCurmb();
	void dropLive();
	void initPositions();
	void pause();
	void draw();
	void getPossibleDirs(const Position& pos, int possibleDirs[]);
	void fruitSpawn();
	void eatFruit(Fruit* fruit);
};

