#pragma once

#include "Game.h"
#include "Board.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Fruit.h"
#include "Menu.h"
#include <string>
#include <iostream>
#include <list>

class Game {
	enum { ESC = 27, LIVES = 3 };
	Board gameBoard;
	Pacman* player;
	list<GameObject*> gameObjects;
	int points=0, lives=LIVES;
	bool isColors = true;
	bool isErrorInInit = false;
	bool isInProgress = false;
	int speed = 200;
	int fruitAmount = 0;
	int maxFruitAmount = 5;
	int maxGhostsAmount = 2;
	int level = 1;
	Menu menu;
public:
	void startMenu();
private:
	void setPlayer(Pacman* p) { player = p; };
	void init();
	void run();
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

