#pragma once
#include "Position.h"

class Ghost {
	Position pos;
	const char sign = '$';
public:
	void move(int possibleDirs[], char prevChar);
	void draw();
	void initPos();
	Position getPos() { return pos; };
private:
	void undraw();
};