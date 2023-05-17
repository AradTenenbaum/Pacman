#pragma once
#include "Position.h"
#include "utils.h"
#include "GameObject.h"

class Pacman : public GameObject {
public:
	Pacman() : GameObject('@', DEFAULT) {};
	void move(int dir);
	void initPos();
};