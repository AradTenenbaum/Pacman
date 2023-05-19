#pragma once
#include "Position.h"
#include "utils.h"
#include "GameObject.h"

class Pacman : public GameObject {
public:
	Pacman(Position& startPos) : GameObject('@', DEFAULT, startPos) {};
	void move(int dir) override;
};