#pragma once
#include "GameObject.h"
#include "utils.h"

class Fruit : public GameObject {
	int ttl;
public:
	Fruit() : 
		GameObject(getRandomNumber(5, 9) + '0', DEFAULT), 
		ttl(getRandomNumber(5, 15)) {};
	void initPos();
	int getVal() { return sign - '0'; };
	void turn();
	bool isDead() { return ttl == 0; };
};