#include "Ghost.h"
#include <iostream>
#include <cstdlib>
#include "utils.h"

using namespace std;

void Ghost::smartMove(const Position& target, int possibleDirs[]) {
	prevPos = pos;

	int dir = -1;
	if (target.getX() < pos.getX() && (possibleDirs[0] == 1)) {
		dir = 0;
	}
	else if (target.getX() > pos.getX() && (possibleDirs[1] == 1)) {
		dir = 1;
	}
	else if (target.getY() < pos.getY() && (possibleDirs[2] == 1)) {
		dir = 2;
	}
	else if (target.getY() > pos.getY() && (possibleDirs[3] == 1)) {
		dir = 3;
	}

	if (dir == 0) {
		pos.addX(-1);
	}
	if (dir == 1) {
		pos.addX(1);
	}
	if (dir == 2) {
		pos.addY(-1);
	}
	if (dir == 3) {
		pos.addY(1);
	}
}