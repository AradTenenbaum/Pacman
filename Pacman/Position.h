#pragma once
#include "Position.h"

class Position {
	int x = 1, y = 1;
public:
	Position(int _x, int _y) : x(_x), y(_y) {};
	Position() : x(1), y(1) {};
	void addX(int xAdd) { x += xAdd; };
	void addY(int yAdd) { y += yAdd; };
	int getX() const { return x; };
	int getY() const { return y; };
	void setPos(int _x, int _y);
	Position posAfterMove(int dir);
	bool operator==(const Position& p) const { return (p.getX() == x && p.getY() == y); };
	bool isTunnel(int dir);
};