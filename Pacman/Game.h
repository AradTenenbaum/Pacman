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
	list<GameObject*> gameObjects;
	int points=0, lives=LIVES;
	bool isColors = true;
	int speed = 200;
	int fruitAmount = 0;
	int maxFruitAmount = 5;
	int maxGhostsAmount = 2;
	int level = 1;
	bool isErrorInInit = false;
public:
	void displayMenu();
	void displayInstructions();
	void displaySettings();
	void displayLevels();
	void init();
	void run();
	void setPlayer(Pacman* p) { player = p; };
	void setColors() { isColors = !isColors; };
private:
	void setStats();
	void setLevel(int _level) { level = _level; };
	void levelUp() { level++; };
	void levelDown() { if(level > 1) level--; };
	void addPoints(int add);
	bool isValidMove(int dir);
	bool onBreadCurmb();
	bool isFreeSpot(Position& spot);
	void dropLive();
	void initPositions();
	void pause();
	void draw();
	void getPossibleDirs(const Position& pos, int possibleDirs[]);
	void fruitSpawn(Position& spot);
	void eatFruit(Fruit* fruit);
	void fruitDisappear(Fruit* fruit);
};

