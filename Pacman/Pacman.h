#pragma once
#include "Position.h"
#include "utils.h"

class Pacman {
	Position pos;
	const char sign = '@';
	char color = DEFAULT;
public:
	void move(int dir);
	void draw();
	void initPos();
	Position getPos() { return pos; };
	void setColor(int _color) { color = _color; };
private:
	void undraw();
};