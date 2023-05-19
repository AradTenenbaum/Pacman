#pragma once
#include "Position.h"
#include "utils.h"
#include "GameObject.h"

class Ghost : public GameObject {
public:
	Ghost(Position& startPos) : GameObject('$', DEFAULT, startPos) {};
	void smartMove(const Position& target, int possibleDirs[]);
};