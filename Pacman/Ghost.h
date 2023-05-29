#pragma once
#include "Position.h"
#include "utils.h"
#include "Board.h"
#include "GameObject.h"


class Ghost : public GameObject {
	int mode = NORMAL;
	int chosenDir = NOT_FOUND;
public:
	Ghost(Position& startPos) : GameObject('$', DEFAULT, startPos) {};
	void smartMove(const Position& target, int possibleDirs[]);
	void aStarSearch(Board board, const Position& src, const Position& dest);
	void setMode(int _mode) { mode = _mode; };
	int getMode() { return mode; };
	void setChosenDir(int _chosenDir) { chosenDir = _chosenDir; };
	int getChosenDir() { return chosenDir; };
	//void aStarSearch(char grid[][COL], Pair src, Pair dest);
};