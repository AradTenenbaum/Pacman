#pragma once
#include "Position.h"
#include "utils.h"
#include "GameObject.h"

class Ghost : public GameObject {
public:
	Ghost() : GameObject('$', DEFAULT) {};
	void move(int dir);
	void initPos();
};