#pragma once
#include "Position.h"

class Pacman {
	Position pos;
	const char sign = '@';
public:
	void move(int dir);
	void draw();
	void initPos();
	Position getPos() { return pos; };
private:
	void undraw();
};