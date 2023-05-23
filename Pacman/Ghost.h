#pragma once
#include "Position.h"
#include "utils.h"
#include "Board.h"
#include "GameObject.h"

#define ROW 24
#define COL 81

class Ghost : public GameObject {
public:
	Ghost(Position& startPos) : GameObject('$', DEFAULT, startPos) {};
	void smartMove(const Position& target, int possibleDirs[]);
	void aStarSearch(Board board, const Position& src, const Position& dest);
	//void aStarSearch(char grid[][COL], Pair src, Pair dest);
};