#pragma once
#include "GameObject.h"
#include "utils.h"

class Fruit : public GameObject {
public:
	Fruit() : GameObject(getRandomNumber(5, 9) + '0', DEFAULT) {};
	void move(int dir);
	void initPos();
	int getVal() { return sign - '0'; };
};