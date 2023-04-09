#pragma once
#include "Position.h"

class Position {
	int x = 1, y = 1;
public:
	Position(int _x, int _y) : x(_x), y(_y) {};
	Position() : x(1), y(1) {};
	void addX(int xAdd) { x += xAdd; };
	void addY(int yAdd) { y += yAdd; };
	int getX() { return x; };
	int getY() { return y; };
	void setPos(int _x, int _y);
	Position posAfterMove(int dir);
	bool isTunnel(int dir);
};