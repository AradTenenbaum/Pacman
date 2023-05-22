#pragma once
#include "Position.h"
#include "utils.h"
#include "GameObject.h"

#define ROW 81
#define COL 24
// Creating a shortcut for int, int pair type
typedef pair<int, int> Pair;
// Creating a shortcut for pair<int, pair<int, int>> type
typedef pair<double, pair<int, int> > pPair;

class Ghost : public GameObject {
public:
	Ghost(Position& startPos) : GameObject('$', DEFAULT, startPos) {};
	void smartMove(const Position& target, int possibleDirs[]);
	void aStarSearch(char board[HEIGHT][WIDTH], Position& src, Position& dest);
	void aStarSearch(char grid[][COL], Pair src, Pair dest);
};