#include <iostream>
#include "Pacman.h"
#include "utils.h"

using namespace std;

void Pacman::move(int dir) {
	undraw();

	if ((dir == LEFT) || (dir == LEFT_L)) {
		pos.addX(-1);
	}
	else if ((dir == RIGHT) || (dir == RIGHT_L)) {
		pos.addX(1);
	}
	else if ((dir == UP) || (dir == UP_L)) {
		pos.addY(-1);
	}
	else if ((dir == DOWN) || (dir == DOWN_L)) {
		pos.addY(1);
	}
}

void Pacman::draw() {
	gotoxyPos(pos);
	cout << sign;
}

void Pacman::undraw() {
	gotoxyPos(pos);
	cout << ' ';
}

void Pacman::initPos() {
	pos.setPos(1, 1);
}